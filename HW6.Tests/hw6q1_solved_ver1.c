#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_NUMS 100

int getNums();
void swap();
void printArr();

//=========================================================================

void bubbleSort(int nums[MAX_NUMS], int count) {
    bool isSorted = false;
    int last = count - 1;
    while (!isSorted) {
        isSorted = true;
        for (int i = 0; i < last; i++) {
            if (nums[i] > nums[i + 1]) {
                isSorted = false;
                swap(nums + i, nums + i + 1);
            }
        }
        last--;
    }
}

void maxSort(int nums[MAX_NUMS], int count) {
    for (int last = count - 1; last > 0; last--) {
        int max = 0;
        int maxLoc = 0;
        //find the max
        for (int i = 0; i <= last; i++) {
            if (nums[i] > max) {
                max = nums[i];
                maxLoc = i;
            }
        }

        //put it in the end
        swap(nums + last, nums + maxLoc);
    }
}

void maxSortRecursive(int nums[MAX_NUMS], int count) {
    if (count == 1) return;
    int max = 0;
    int maxLoc = 0;
    //find the max
    for (int i = 0; i < count; i++) {
        if (nums[i] > max) {
            max = nums[i];
            maxLoc = i;
        }
    }
    //put it in the end
    swap(nums + count - 1, nums + maxLoc);

    //recursive call
    maxSortRecursive(nums, count - 1);
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

    maxSortRecursive(nums, count);

    printArr(nums, count);

    return (EXIT_SUCCESS);
}

