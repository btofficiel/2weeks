#include <stdio.h>

void displayArray(int arr[], int size) {
    printf("Using array notation\n");
    for(int i=0; i<size; i++) {
        printf("Element at position %d: %d\n", i, arr[i]);
    }
}

void displayArrayUsingPointerNotation(int *arr, int size) {
    printf("Using pointer notation\n");
    for(int i=0; i<size; i++) {
        // arr is the base address of the array
        // arr+i is the address of the ith element
        // *(arr+i) is the value at the ith element of the array
        printf("Element at position %d: %d\n", i, *(arr+i));
    }
}

int main() {
    int vector[5] = {1,2,3,4,5};
    displayArray(vector, 5);
    displayArrayUsingPointerNotation(vector, 5);

    return 0;
}
