#include <stdio.h>
#include <stdlib.h>

char* getLine() {
    // Initial size of the buffer
    const size_t sizeIncrement = 10;
    // Using malloc to allocated memory for the buffer
    char* buffer = (char*) malloc(sizeIncrement);
    // Pointer to store the next character
    char* currentPosition = buffer;

    //Max length of the buffer
    size_t maxLength = sizeIncrement;
    // Current length of the string
    size_t length = 0;

    //Storing current character
    int character;

    // If memory allocation fails
    if(currentPosition == NULL) return NULL;

    while(1) {
        character = fgetc(stdin);

        if(character == '\n') { break; }

        if(++length >=maxLength) {
            // Allocate new buffer with increased max length
            char* newBuffer = (char*) realloc(buffer, maxLength+=sizeIncrement);

            if(newBuffer == NULL) return NULL;

            // Set new position accordingly
            currentPosition = newBuffer + (currentPosition-buffer);
            buffer = newBuffer;
        }
        *currentPosition++= character;
    }

    *currentPosition = '\0';
    return buffer;
}

int main() {
    char* str = (char*) getLine();

    printf("Text: %s\n", str);

    free(str);

    return 0;
}
