#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* format(char *buffer, size_t size, const char *name, size_t quantity, size_t weight) {
    char *formatString = "Item: %s Quantity: %u Weight: %u";
    // Subtrating format specifier length from formatString length
    size_t formatStringLength = strlen(formatString)-6;
    size_t nameLength = strlen(name);
    // Assuming max digits for quantity and weight to be 10 and 1 extra character for NUL
    size_t length = formatStringLength+nameLength+10+10+1;

    // If buffer is NULL pointer then allocate memory 
    if(buffer==NULL) {
        buffer = (char*) malloc(length);
        size = length;
    }

    snprintf(buffer, size, formatString, name, quantity, weight);
    return buffer;
}

int main() {
    char *result = format(NULL, 0, "Mangoes", 2, 5);

    printf("%s\n", result);

    free(result);

    return 0;
}
