#include <stdio.h>

int main() {
    int num1 = 1;
    const int num2 = 2;
    int num3 = 3;
    
    int *pi= &num1;

    const int *pci = &num2;

    //Const pointer to a non constant
    int *const cpi = &num3;

    // Will error because using a non constant pointer with a constant int
    // Using clang -> constant_pointers.c:11:10: warning: initializing 'int *' with an expression of type 'const int *' discards qualifiers [-Wincompatible-pointer-types-discards-qualifiers
    int *pi2 = &num2;

    *pi = 5;

    // Will throw an error as is is modifying a constant integer
    // Using clang -> constant_pointers.c:14:10: error: read-only variable is not assignable
    *pci = 100;

    *cpi = 7;

    // Will throw an error
    // // Using clang -> constant_pointers.c:13:16: note: variable 'cpi' declared const here
    cpi = &num1;
    

    printf("Value num1: %d\n", *pi);
    printf("Value num2: %d\n", *pci);
    printf("Value num3: %d\n", *cpi);

    return 0;
}
