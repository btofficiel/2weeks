#include <stdio.h>


void swapWithPointers(int* pnum1, int* pnum2) {
    int tmp;
    tmp = *pnum1;
    *pnum1 = *pnum2;
    *pnum2 = tmp;
}

int main() {
    int n1 = 5;
    int n2 = 6;

    printf("Value before swapping n1: %d\n", n1);
    printf("Value before swapping n2: %d\n", n2);

    // Swap values
    swapWithPointers(&n1, &n2);


    printf("Value after swapping n1: %d\n", n1);
    printf("Value after swapping n2: %d\n", n2);

    return 0;
}
