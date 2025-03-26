#include <stdio.h>

void swap(int num1, int num2) {
    int tmp;
    tmp = num1;
    num1 = num2;
    num2 = num1;
}

int main() {
    int num1 = 5;
    int num2 = 6;

    printf("Value before swap n1: %d\n", num1);
    printf("Value before swap n2: %d\n", num2);

    // Swap values
    printf("Value after swap n1: %d\n", num1);
    printf("Value after swap n2: %d\n", num2);

    return 0;
}
