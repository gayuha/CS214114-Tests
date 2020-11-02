/* 
 * File:   hw5q1testmaker.c
 * Author: Guy Shapira
 *
 * Created on January 11, 2019, 3:15 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

void printConstantMatrix(FILE *filePointer, int rows, int columns, int num){
    for(int i=0; i<rows; i++){
        for(int j=0; j<columns; j++){
            if(j==i){
                fprintf(filePointer, "%d", 0);
            }else{
                fprintf(filePointer, "%d", num);
            }
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
            if(j==i){
                fprintf(filePointer, "0");
            }else{
                int no_road = rand() % 10;
                int num = rand() % 99 + 1;
                fprintf(filePointer, "%d", no_road<3 ? -1 : num);
            }
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
    
    //4x4, numbers: 1-10
    for(int i=1; i<=10; i++){
        char filename[50];
        FILE *testfile_pointer;
        sprintf(filename, "hw5q1in%d.txt", testNumber);
        testfile_pointer = fopen(filename, "w");
        
        printConstantMatrix(testfile_pointer, 4, 4, i);
        
        fclose(testfile_pointer); 
        
        testNumber++;
    }
    
    //all sizes, random numbers
    while(testNumber<=2000){
        char filename[50];
        FILE *testfile_pointer;
        sprintf(filename, "hw5q1in%d.txt", testNumber);
        testfile_pointer = fopen(filename, "w");
        
        printRandomMatrix(testfile_pointer, 4, 4);
        
        fclose(testfile_pointer); 
        
        testNumber++;
    }
    
    return (0);
}

