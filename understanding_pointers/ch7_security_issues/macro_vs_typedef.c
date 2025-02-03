#include <stdio.h>

#define PRINT_TYPE(x) _Generic((x), \
    int: "int", \
    int*: "int*", \
    default: "unknown" \
)

#define PINT int*

typedef int* INTPTR;


int main() {
    PINT p1, p2;
    INTPTR p3, p4;

    printf("Type p1: %s\n", PRINT_TYPE(p1));
    // Will print int instead of int* 
    // Compiler doens't perform type checks on macros
    // Macros perform simple text substitution 
    // so the int* only applies to the first variable after it
    printf("Type p2: %s\n", PRINT_TYPE(p2));
    printf("Type p3: %s\n", PRINT_TYPE(p3));
    printf("Type p4: %s\n", PRINT_TYPE(p4));

    return 0;
}
