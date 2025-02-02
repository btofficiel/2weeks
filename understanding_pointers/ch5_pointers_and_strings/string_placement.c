#include <stdio.h>
#include <string.h>

char* globalHeader = "Hello";
char globalArrayHeader[] = "Hello";

void displayHeader() {
    static char* staticHeader = "Hello";
    printf("Address of static header: %p\n", staticHeader);
}

int main() {
    // Both are equal because both are referring to same string literal in 
    // the string literal pool
    displayHeader();
    printf("Address of global header: %p\n", globalHeader);
    
    return 0;
}

