#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

void print(const int* arr, int n) {
    for (int i = 0; i < n; ++i) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

void insertion_sort(int* arr, int size) {
    for (int i = 2; i <= size; ++i) {
        int key = arr[i - 1];
        int j = i - 1;
        while (j >= 1 && arr[j - 1] > key) {
            arr[j] = arr[j - 1];
            j--;
        }
        arr[j] = key;
        print(arr, size);
    }
}

int main(int argc, const char* argv[]) {
    srand(time(NULL));
    const int size = 10;
    int* arr = (int*)calloc(size, sizeof(int));
    for (int i = 0; i < size; ++i) {
        arr[i] = rand() % 100;
    }
    insertion_sort(arr, size);
    free(arr);
    return 0;
}