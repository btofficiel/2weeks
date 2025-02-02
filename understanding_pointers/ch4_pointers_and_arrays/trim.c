#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* trim(char* phrase) {
    // For scanning 
    char *old = phrase;
    // For writing
    char *new = phrase;

    // Skip all  ' ' characters
    while(*old == ' ') {
        old++;
    }

    while(*old) {
        // Put the trimmed string at the beginning
        *(new++) = *(old++);
    }

    *new = 0;
    return (char *) realloc(phrase, strlen(phrase)+1);
}

int main() {
    char *buffer = (char *) malloc(strlen("  cat")+1);
    strcpy(buffer, "  cat");
    printf("Trimmed '  cat': %s\n", trim(buffer));

    return 0;
}
