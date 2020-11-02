/* 
 * File:   hw2q3testmaker.c
 * Author: gayuh
 *
 * Created on November 24, 2018, 5:02 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void printConstantMatrix(FILE *filePointer, int size, int num){
    for(int i=0; i<size; i++){
        for(int j=0; j<size; j++){
            fprintf(filePointer, "%d", num);
            if(j!=size-1){
                fprintf(filePointer, " ");
            }
        }
        if(i!=size-1){
            fprintf(filePointer, "\n");
        }
    }
}

void printRandomMatrix(FILE *filePointer, int size){
    for(int i=0; i<size; i++){
        for(int j=0; j<size; j++){
            fprintf(filePointer, "%d", rand() % 256);
            if(j!=size-1){
                fprintf(filePointer, " ");
            }
        }
        if(i!=size-1){
            fprintf(filePointer, "\n");
        }
    }
}

/*
 * 
 */
int main() {
    srand(time(0));
    int testNumber = 5;
    
    //25x25, numbers: 0-9
    for(int i=0; i<=9; i++){
        char filename[50];
        FILE *testfile_pointer;
        sprintf(filename, "hw2q3in%d.txt", testNumber);
        testfile_pointer = fopen(filename, "w");
        
        fprintf(testfile_pointer, "%d", rand()%500);//number of iterations
        fprintf(testfile_pointer, "\n");
        fprintf(testfile_pointer, "%d", 25);//size
        fprintf(testfile_pointer, "\n");
        printConstantMatrix(testfile_pointer, 25, i);
        
        fclose(testfile_pointer); 
        
        testNumber++;
    }
    
    //all sizes, random numbers
    for(int i=1; i<=25; i++){
        char filename[50];
        FILE *testfile_pointer;
        sprintf(filename, "hw2q3in%d.txt", testNumber);
        testfile_pointer = fopen(filename, "w");
        
        fprintf(testfile_pointer, "%d", rand()%500);//number of iterations
        fprintf(testfile_pointer, "\n");
        fprintf(testfile_pointer, "%d", i);//size
        fprintf(testfile_pointer, "\n");
        printRandomMatrix(testfile_pointer, i);
        
        fclose(testfile_pointer); 
        
        testNumber++;
    }
    
    //random size, random numbers
    for(int i=0; i<100; i++){
        char filename[50];
        FILE *testfile_pointer;
        sprintf(filename, "hw2q3in%d.txt", testNumber);
        testfile_pointer = fopen(filename, "w");
        
        fprintf(testfile_pointer, "%d", rand()%500);//number of iterations
        fprintf(testfile_pointer, "\n");
        int size = rand()%25+1;
        fprintf(testfile_pointer, "%d", size);//size
        fprintf(testfile_pointer, "\n");
        printRandomMatrix(testfile_pointer, size);
        
        fclose(testfile_pointer); 
        
        testNumber++;
    }
    
    //invalid amount of iterations
    for(int i=0; i<50; i++){
        char filename[50];
        FILE *testfile_pointer;
        sprintf(filename, "hw2q3in%d.txt", testNumber);
        testfile_pointer = fopen(filename, "w");
        
        int junkIteratons = rand()%10+1;
        for(int j=0; j<junkIteratons; j++){
            fprintf(testfile_pointer, "%d", -rand()%500 - 1);//junk number of iterations
            fprintf(testfile_pointer, "\n");
        }
        fprintf(testfile_pointer, "%d", rand()%500);//number of iterations
        fprintf(testfile_pointer, "\n");
        int size = rand()%25+1;
        fprintf(testfile_pointer, "%d", size);//size
        fprintf(testfile_pointer, "\n");
        printRandomMatrix(testfile_pointer, size);
        
        fclose(testfile_pointer); 
        
        testNumber++;
    }
    
    return (0);
}

