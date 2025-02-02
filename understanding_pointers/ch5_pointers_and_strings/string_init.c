#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    char header[] = "Media Player";

    char header2[13];
    strcpy(header2, "Media Player");

    char *header_ptr = (char*) malloc(13);
    strcpy(header_ptr, "Media Player");

    printf("Value: %s\n", header);
    printf("Value: %s\n", header2);
    printf("Value: %s\n", header_ptr);

    char *header_input;
    printf("Enter a value: ");
    scanf("%s", header_input);

    printf("Input: %s\n", header_input);

    free(header_ptr);

    return 0;
} 
