/*
 * File:   TestRunner.c
 * Author: Guy Shapira
 *
 * Created on November 15, 2018, 8:09 PM
 */

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
 * Compares two files. Returns 0 if they are equal, 1 otherwise.
 */
int CompareFiles(char* pFname1, char* pFname2) {
    FILE *pFile1, *pFile2;
    long lSize1, lSize2; // file length
    int i = 0;
    char tmp1, tmp2;

    pFile1 = fopen(pFname1, "r");
    pFile2 = fopen(pFname2, "r");

    // obtain file size:
    fseek(pFile1, 0, SEEK_END);
    lSize1 = ftell(pFile1);
    rewind(pFile1);

    // obtain file size:
    fseek(pFile2, 0, SEEK_END);
    lSize2 = ftell(pFile2);
    rewind(pFile2);

    if (lSize1 != lSize2) {
        return (1);
    }
    for (i = 0; i < lSize1; i++) {
        fread(&tmp1, 1, 1, pFile1);
        fread(&tmp2, 1, 1, pFile2);
        if (tmp1 != tmp2) {
            fclose(pFile1);
            fclose(pFile2);
            return (1);
        }
    }
    fclose(pFile1);
    fclose(pFile2);
    return (0);
}

/*
 * Check if a file exist using fopen() function
 * return 1 if the file exist otherwise return 0
 */
int fileExists(const char* filename) {
    /* try to open file to read */
    FILE* file;
    if ((file = fopen(filename, "r"))) {
        fclose(file);
        return 1;
    }
    return 0;
}

void pause() {
    // just for pausing
    printf("Press Enter to continue...");
    getchar();
}

int launchDiffMerge(int test, int hw, int q) {
    char filename[70];
    char* filenames[70] = {"C://Program Files//SourceGear//Common//DiffMerge//sgdm.exe",
                           "C://Program Files (x86)//SourceGear//Common//DiffMerge//sgdm.exe",
                           "C://Program Files//SourceGear//Common//DiffMerge//diffmerge.exe",
                           "C://Program Files (x86)//SourceGear//Common//DiffMerge//diffmerge.exe"};
    bool found = false;
    for (int i = 0; i < 4; i++) {
        sprintf(filename, filenames[i]);
        if (fileExists(filename)) {
            found = true;
            break;
        }
    }
    if (!found) {
        printf("Diffmerge not found! You may launch it manually though.\n");
    }
    char command[200];
    sprintf(command, "\"%s\" -ro2 -t1=Expected -t2=Yours expected//hw%dq%dout%d.txt actual//hw%dq%dout%d.txt", filename,
            hw, q, test, hw, q, test);
    system(command);
    printf("\n");
    return 0;
}

/*
 * Main
 */
int main(int argc, char** argv) {
    bool generate = false;
    if (argc > 1) {
        if (strcmp(argv[1], "gen_tests") == 0) {
            generate = true;
        }
    }

    printf("~~~~~~~~~~~~~~~~~~~~~~~~Test Runner by Guy Shapira~~~~~~~~~~~~~~~~~~~~~~~~\n");
    printf("This program runs tests on homeworks of course 234114/7 in the Technion.\n"
           "Your executable must be named similar to this example: hw2q1.exe\n"
           "Input file name example: hw2q1in1.txt\n"
           "Expected output file name example: hw2q1out1.txt\n"
           "Inputs are in subfolder \"input\"\n"
           "Outputs are in subfolder \"output\"\n"
           "Your program's output files will be created in subfolder \"actual\"\n"
           "If some tests fail, Diffmerge will be launched on the first failing test.\n"
           "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n"
           "Version 1.3\n\n\n");

    if (generate) {
        printf("In generation mode!!!\n");
    }

    int hw, q;
    char exe[50];
    bool exists = false;
    for (hw = 0; hw < 10; hw++) {
        for (q = 0; q < 10; q++) {
            sprintf(exe, "hw%dq%d.exe", hw, q);
            if (fileExists(exe)) {
                exists = true;
                break;
            }
        }
        if (exists)
            break;
    }

    if (!exists) {
        printf("Executable not found!\n"
               "Make sure you copied the exe file and not the c file.\n"
               "Make sure you named it correctly, e.g: hw2q3.exe\n"
               "Make sure that the testrunner and your exe are in the same folder.\n"
               "Program will quit.\n\n");
        pause();
        return (1);
    }
    printf("Executable hw%dq%d.exe found! Starting tests...\n", hw, q);

    int passed = 0, failed = 0, firstFail = 0, missing = 0;
    printf("===TESTS BEGIN===\n");
    system("if not exist actual//nul mkdir actual");
    if (generate) {
        system("if not exist expected//nul mkdir expected");
    }
    for (int i = 1; i <= 2000; i++) {
        char input_filename[50], expected_out_filename[50], actual_out_filename[50];
        sprintf(input_filename, "input//hw%dq%din%d.txt", hw, q, i);
        if (!fileExists(input_filename)) {
            break;
        }
        sprintf(expected_out_filename, "expected//hw%dq%dout%d.txt", hw, q, i);
        sprintf(actual_out_filename, "actual//hw%dq%dout%d.txt", hw, q, i);
        char command[100];
        sprintf(command, "hw%dq%d.exe < %s > %s", hw, q, input_filename,
                generate ? expected_out_filename : actual_out_filename);
        system(command);

        if (generate) {
            printf("Test number %d generated!\n", i);
            passed++;
            continue;
        }
        if (!fileExists(expected_out_filename)) {
            printf("->Test number %d is missing!\n", i);
            missing++;
        } else if (CompareFiles(expected_out_filename, actual_out_filename)) {
            printf("->Test number %d failed!\n", i);
            firstFail = firstFail == 0 ? i : firstFail;
            failed++;
        } else {
            printf("Test number %d passed!\n", i);
            passed++;
        };
    }
    printf("===TESTS END===\n");
    if (generate) {
        printf("Total tests generated: %d\n\n", passed);
    } else {
        printf("Passed: %d | Failed: %d | Missing: %d | Total: %d\n", passed, failed, missing,
               passed + failed + missing);
        if (passed + failed == 0) {
            printf("\nNo tests were found!\n"
                   "Make sure they are in the input directory.\n"
                   "Make sure you named your exe with the correct hw number and q number.\n"
                   "Program will quit.\n\n");
            pause();
            return (0);
        }
        if (missing != 0) {
            printf("Some tests are missing.\n\n");
        } else if (failed == 0) {
            printf("All tests passed. Congratulations!\n\n");
        } else {
            printf("Some tests failed. Check carefully with Diffmerge!\n\n");
            printf("The first failing test is: %d\n", firstFail);
            launchDiffMerge(firstFail, hw, q);
        }
    }

    pause();
    return (0);
}
