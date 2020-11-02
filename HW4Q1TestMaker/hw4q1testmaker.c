/* 
 * File:   hw4q1testmaker.c
 * Author: Guy Shapira
 *
 * Created on December 28, 2018, 11:34 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

void printConstantMatrix(FILE *filePointer, int rows, int columns, double num){
    for(int i=0; i<rows; i++){
        for(int j=0; j<columns; j++){
            fprintf(filePointer, "%.2f", num);
            if(j!=columns-1){
                fprintf(filePointer, " ");
            }
        }
        if(i!=rows-1){
            fprintf(filePointer, "\n");
        }
    }
}

void printRandomMatrix(FILE *filePointer, int rows, int columns){
    for(int i=0; i<rows; i++){
        for(int j=0; j<columns; j++){
            int positive = rand() % 2;
            double num = rand() % 1000 + (rand() % 100)/100.0;
            fprintf(filePointer, "%.2f", positive ? num : -num);
            if(j!=columns-1){
                fprintf(filePointer, " ");
            }
        }
        if(i!=rows-1){
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
    
    //100x100, numbers: (-9)-9
    for(int i=-9; i<=9; i++){
        char filename[50];
        FILE *testfile_pointer;
        sprintf(filename, "hw4q1in%d.txt", testNumber);
        testfile_pointer = fopen(filename, "w");
        
        fprintf(testfile_pointer, "%d %d", 100, 100);//size
        fprintf(testfile_pointer, "\n");
        printConstantMatrix(testfile_pointer, 100, 100, i);
        
        fclose(testfile_pointer); 
        
        testNumber++;
    }
    
    //all sizes, random numbers
    for(int i=1; i<=100; i++){
        char filename[50];
        FILE *testfile_pointer;
        sprintf(filename, "hw4q1in%d.txt", testNumber);
        testfile_pointer = fopen(filename, "w");
        
        fprintf(testfile_pointer, "%d %d", i, i);//size
        fprintf(testfile_pointer, "\n");
        printRandomMatrix(testfile_pointer, i, i);
        
        fclose(testfile_pointer); 
        
        testNumber++;
    }
    
    //random size, random numbers
    for(int i=0; i<2000; i++){
        char filename[50];
        FILE *testfile_pointer;
        sprintf(filename, "hw4q1in%d.txt", testNumber);
        testfile_pointer = fopen(filename, "w");
        
        int rows = rand()%100+1;
        int columns = rand()%100+1;
        fprintf(testfile_pointer, "%d %d", rows, columns);//size
        fprintf(testfile_pointer, "\n");
        printRandomMatrix(testfile_pointer, rows, columns);
        
        fclose(testfile_pointer); 
        
        testNumber++;
    }
    
    return (0);
}

