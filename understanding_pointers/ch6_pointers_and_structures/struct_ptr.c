#include <stdlib.h>
#include <stdio.h>

typedef struct _person {
    char* name;
    int age;
} Person;

int main() {
    Person* prsnPtr;
    prsnPtr = (Person*) malloc(sizeof(Person));
    prsnPtr->name = "Bhaskar";
    prsnPtr->age = 87;

    printf("Name: %s, Age: %d\n", prsnPtr->name, prsnPtr->age);

    return 0;
}

