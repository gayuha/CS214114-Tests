/* 
 * File:   hw2q2testmaker.c
 * Author: Guy Shapira
 *
 * This is a test maker for hw2q2
 * Created on November 22, 2018, 3:26 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void printNumbers(FILE *filePointer, int length){
    for(int j=0; j<length; j++){
        fprintf(filePointer, "%d", rand() % 13 + 1);
        fprintf(filePointer, " ");
    }
}

/*
 * 
 */
int main() {
    srand(time(0)); 
    //files 1-4 are given, 5 is manually create no-vote test
    for(int i=6; i<200; i++){
        char filename[50];
        FILE *testfile_pointer;
        sprintf(filename, "hw2q2in%d.txt", i);
        testfile_pointer = fopen(filename, "w");
        
        char a = rand() % 93 + 33;
        fprintf(testfile_pointer, "%c", a);
        fprintf(testfile_pointer, "\n");
        
        printNumbers(testfile_pointer, rand() % 100 + 1);
        
        fprintf(testfile_pointer, "-1");
        fclose(testfile_pointer); 
    }
    //generate some files with "-1" in the middle
    for(int i=200; i<250; i++){
        char filename[50];
        FILE *testfile_pointer;
        sprintf(filename, "hw2q2in%d.txt", i);
        testfile_pointer = fopen(filename, "w");
        
        char a = rand() % 93 + 33;
        fprintf(testfile_pointer, "%c", a);
        fprintf(testfile_pointer, "\n");
        
        printNumbers(testfile_pointer, rand() % 30 + 1);
        fprintf(testfile_pointer, "-1 ");
        printNumbers(testfile_pointer, rand() % 30 + 1);
        
        fclose(testfile_pointer); 
    }
    return (0);
}

