#include <stdio.h>
#include <stdlib.h>

void saferFree(void **pp) {
    if(pp != NULL && *pp != NULL) {
        free(*pp);
        *pp = NULL;
    }
}

int main() {
    int *num = (int*) malloc(sizeof(int));

    *num = 10;

    printf("Value before saferFree: %d\n", *num);

    saferFree(&num);

    // Will print OxO which is a valid NULL value
    printf("Address after saferFree: %p\n", num);

    return 0;
}


