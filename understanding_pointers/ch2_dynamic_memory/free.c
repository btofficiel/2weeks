#include <stdio.h>
#include <stdlib.h>

int main() {
    int *pi = (int*) malloc(sizeof(int));
    *pi = 5;
    free(pi);
    // Doesn't print 5
    printf("Value: %d\n", *pi);

    //Assigning null to prevent unspeicified behaviour during dereferrencing
    pi = NULL;
    // Will throw a segmentation fault error
    printf("Value after assiogning NULL: %d\n", *pi);

    return 0;
}
