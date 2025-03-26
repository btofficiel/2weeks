#include <stdlib.h>

int main() {
    //Will throw an error since you cannot use a function to initialise a static or global variable
    // Using clang -> static_vars.c:5:23: error: initializer element is not a compile-time constant
    static int *spi = malloc(sizeof(int));

    // This will work because we are using malloc during assignment and not initialisation
    static int *pi;
    pi = malloc(sizeof(int));

    return 0;
}
