/*
This is an exercise for implementing sorting algorithms.
The tests for this are of varying lengths, from 5 numbers up to 50.
Every number is at least 10 and no greater than 99.
Numbers are seperated by spaces and end with a -1.

I've written the code to input the numbers into an array. 
Your job is to write a function that sorts the array. Then you should call it from the main function.
You can use the swap fuction to swap array elements.

By Guy Shapira
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_NUMS 100

int getNums();
void swap();
void printArr();

//=========================================================================

void mySort(int nums[MAX_NUMS], int count){
	//implement your sorting algorithm here!
}

//=========================================================================

int getNums(int nums[MAX_NUMS]) {
    int num = 0;
    int index = 0;
    while (scanf("%d", &num) != EOF && num != -1) {
        nums[index] = num;
        index++;
    }
    return index;
}

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void printArr(int nums[MAX_NUMS], int count) {
    for (int i = 0; i < count; i++) {
        printf("%d ", nums[i]);
    }
}

int main() {
    int nums[MAX_NUMS] = {0};
    int count = getNums(nums);

    mySort(nums, count); //call your sorting function

    printArr(nums, count);

    return (EXIT_SUCCESS);
}

