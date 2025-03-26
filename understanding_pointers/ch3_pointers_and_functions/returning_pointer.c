#include <stdio.h>
#include <stdlib.h>

int *allocateArray(int size, int value) {
    // Allocate nume of elements * size of one element worth of memory
    int *arr = (int*) malloc(size*(sizeof(int)));
    for(int i=0; i<size;i++) {
        arr[i] = value;
    }

    // Return pointer to the array
    return arr;
}

int main() {
    int* vector = allocateArray(8, 10);

    // print 8 times 10
    for(int i=0; i<8;i++) {
        printf("%d\n", vector[i]);
    }

    return 0;
}

