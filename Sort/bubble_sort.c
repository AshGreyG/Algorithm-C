#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>

void print(const int* arr, int n) {
    for (int i = 0; i < n; ++i) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

void swap(int* first, int* second) {
    int temp = *first;
    *first = *second;
    *second = temp;
}

void bubble_sort(int* arr, int size, bool invert) {
    bool flag = true;
    if (invert) {
        while (flag) {
            flag = false;
            for (int i = 0; i < size - 1; ++i) {
                if (arr[i] < arr[i + 1]) {
                    flag = true;
                    swap(&arr[i], &arr[i + 1]);
                }
                print(arr, size);
            }
        }
    } else {
        while (flag) {
            flag = false;
            for (int i = 0; i < size - 1; ++i) {
                if (arr[i] > arr[i + 1]) {
                    flag = true;
                    swap(&arr[i], &arr[i + 1]);
                }
                print(arr, size);
            }
        }
    }
}

int main(int argc, const char* argv[]) {
    srand(time(NULL));
    const int size = 10;
    int* arr = (int*)calloc(size, sizeof(int));
    for (int i = 0; i < size; ++i) {
        arr[i] = rand() % 100;
    }
    bubble_sort(arr, size, true);
    free(arr);
    return 0;
}