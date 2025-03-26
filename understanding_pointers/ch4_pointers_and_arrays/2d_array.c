#include <stdio.h>

void display2dArray(int arr[][5], int rows) {
    printf("Using array notation\n");
    for(int i=0; i<rows; i++) {
        for(int j=0; j<5;j++) {
            printf("Element at row %d and postion %d: %d\n", i, j, arr[i][j]);
        }
    }
}

void display2dArrayUsingPointerNotation(int *arr, int rows) {
    printf("Using pointer notation\n");
    for(int i=0; i<rows; i++) {
        for(int j=0; j<5;j++) {
            printf("Element at row %d and position %d: %d\n", i, j,  *(arr+(i*5)+j));
        }
    }
}

int main() {
    int vector[2][5] = {{1,2,3,4,5}, {6,7, 8, 9, 10}};
    display2dArray(vector, 2);
    display2dArrayUsingPointerNotation(&vector[0][0], 2);

    return 0;
}
