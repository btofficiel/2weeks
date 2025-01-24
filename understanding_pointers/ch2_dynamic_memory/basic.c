#include <stdio.h>
#include <stdlib.h>

int main() {
    // We allocate memory equal to size of an integer.
    // We don't use absolute sizes because this approach is more portable across different environments
    // malloc returns a pointer to the allocated memory and we are explicitly casting it as an int pointer
    int *pi = (int*) malloc(sizeof(int));
    *pi = 5;
    printf("*pi:  %d\n", *pi);
    
    // pi should not be accessed again
    free(pi);

    // However this works so will investigate this in in later code snippets
    *pi = 6;
    printf("*pi:  %d\n", *pi);
    
    return 0;
}
