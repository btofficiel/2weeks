#include <stdlib.h>

int main() {
    int *pi = (int*) malloc(sizeof(int));

    *pi = 5;

    int *pi2 = pi;

    //Double free
    free(pi);
    // Will throw a runtime error
    // Using clang -> malloc: *** error for object 0x600001834030: pointer being freed was not allocated
    free(pi2);

    return 0;
}
