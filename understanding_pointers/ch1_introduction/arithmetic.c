#include <stdio.h>

int main() {
    int nums[] = {1,2,3};

    // Name of the array points to the address of the first element
    int *ptr = nums;

    ptr += 3;

    // Will cycle back to 1 as +3 makes to overflow back to 1
    printf("Value at pointer: %d\n", *ptr);

    return 0;
}
