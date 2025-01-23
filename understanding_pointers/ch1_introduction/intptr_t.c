#include <stdio.h>

int main() {
    char str[] ="Bhaskar Thakur";
    
    // Creating a char pointer to store first character's address
    char *strptr = &str[0];

    // Using an intptr_t to store raw address of this pointer
    intptr_t raw = (intptr_t) strptr;

    // Forwarding the address to 11th element
    raw += 11;

    // Restoring the pointer
    strptr = (char*) raw;

    printf("Character at 11th position: %c\n", *strptr);

    return 0;
}
