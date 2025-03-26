#include <stdio.h>
#include <stdlib.h>

int main() {
    int rows = 2;
    int cols = 5;

    // Allocate memory for pointers to rows

    int **matrix = (int**) malloc(rows*sizeof(int));
    matrix[0] = (int*) malloc(rows*cols*sizeof(int));

    for(int i=0; i<rows;i++){
        matrix[i] = matrix[0]+(i*cols);
    }

    // Print addresses to verify contagiousness
    for(int i=0; i<rows;i++) {
        for(int j=0;j<cols;j++) {
            printf("Address at %d row and %d col: %p\n", i, j, &matrix[i][j]);
        }
    }

    return 0;
}
