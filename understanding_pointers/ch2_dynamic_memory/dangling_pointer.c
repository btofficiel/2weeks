#include <stdlib.h>
#include <stdio.h>

int main() {
    int *pi = (int*) malloc(sizeof(int));

    *pi =5;

    int *pi2;
    pi2 = pi; 

    printf("Value of pi: %d\n", *pi);

    free(pi);
    
    *pi2 = 10; //Dangling pointer

    printf("Value of pi2: %d\n", *pi);

    return 0;
}
