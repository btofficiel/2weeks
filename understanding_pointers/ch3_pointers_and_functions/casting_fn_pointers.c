#include <stdio.h>

typedef int (*fptrTwoInt)(int, int);

int add(int n, int m) {
    return n+m;
}

int main() {
    fptrTwoInt fptr_first = add;
    // Casting it as a fptrTwoInt
    fptrTwoInt fptr_second = (fptrTwoInt) fptr_first;

    printf("Add 1+1 (fptr_first): %d\n", fptr_first(1, 1));
    printf("Add 1+1 (fptr_second): %d\n", fptr_second(1, 1));

    return 0;
}
