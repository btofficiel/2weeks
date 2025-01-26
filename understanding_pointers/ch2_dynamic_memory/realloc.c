#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main() {
    char *string1;
    char *string2;
    string1 = (char*) malloc(16);
    strcpy(string1, "0123456789AB");
    string2 = realloc(string1, 8);
    printf("string1 Value: %p [%s]\n", string1, string1);
    printf("string2 Value: %p [%s]\n", string2, string2);


    char *string3;
    char *string4;

    string3 = (char*) malloc(16);
    strcpy(string3, "0123456789AB");
    string4 = realloc(string3, 64);

    // Interesing that value being printed for string3 is @
    // This is due to realloc freeing the memory block pointed at by string3 
    // after reallocating a larger memory block for string4.
    // Book only mentions copying but doesn't say anything about freeing.
    printf("string3 Value: %p [%s]\n", string3, string3);
    printf("string4 Value: %p [%s]\n", string4, string4);

    return 0;
}

