#include <stdio.h>

int *allocateArray(int size, int value) {
    int arr[size];

    for(int i=0; i<size; i++) {
        arr[i] = value;
    }

    return arr;
}

int main() {
    // Will give a warning
    // Using clang -> passing_local.c:10:12: warning: address of stack memory associated with local variable 'arr' returned [-Wreturn-stack-address]
    int *vector = allocateArray(8, 10);

    for(int i=0; i<8;i++) {
        printf("%d\n", vector[i]);
    }

    return 0;
}
