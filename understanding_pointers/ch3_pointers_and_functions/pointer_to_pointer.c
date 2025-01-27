#include <stdio.h>
#include <stdlib.h>

void allocateArray(int **arr, int size, int value) {
    *arr = (int*) malloc(size*(sizeof(int)));
    if(*arr != NULL) {
        for(int i=0; i<size;i++) {
            // Move pointer by i positions
            // *arr dereferences pointer to pointer and points to arr's base address
            // *(*arr+i) dereferences ith position in arr
            *(*arr+i) = value;
        }
    }
}

int main() {
    int *vector = NULL;

    allocateArray(&vector, 5, 45);

    for(int i=0; i < 5; i++){
        printf("%d\n", vector[i]);
    }

    return 0;
}
