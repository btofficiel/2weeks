#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct _person {
    char* name;
    int age;
} Person;

int main() {
    Person* prsnPtr;
    prsnPtr = (Person*) malloc(sizeof(Person));
    // We need to allocate memory separately because name only stores the address of the first character and
    // not the total value (i.e. "Bhaskar") inside of it
    prsnPtr->name = (char*) malloc(strlen("Bhaskar")+1);
    strcpy(prsnPtr->name, "Bhaskar");
    prsnPtr->age = 87;

    printf("Name: %s, Age: %d\n", prsnPtr->name, prsnPtr->age);

    free(prsnPtr->name);
    free(prsnPtr);

    return 0;
}

