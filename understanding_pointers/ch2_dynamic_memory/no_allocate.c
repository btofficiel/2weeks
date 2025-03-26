#include <stdio.h>

int main() {
    // Results into the following error when using clang
    // bus error  ./no_allocate.o
    // A bus error in C is a runtime error that occurs when a program attempts to access memory in a way that violates the hardware's alignment restrictions.
    char *name;
    printf("Enter a name: ");
    scanf("%s", name);

    return 0;
}
