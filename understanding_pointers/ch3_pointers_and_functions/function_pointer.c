#include <stdio.h>

int sqaure(int n) {
    return n*n;
}

int main() {
    //Function pointer
    // int -> Return type
    // fptr_sq -> Function pointer's varible name
    // (int) -> Function parameters
    int (*fptr_sq)(int);

    fptr_sq = sqaure;

    printf("5 times 5 is: %d\n", fptr_sq(5));

    return 0;
}


