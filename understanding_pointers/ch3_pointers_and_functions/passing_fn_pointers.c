#include <stdio.h>

int add(int n, int m) {
    return n+m;
}

int sub(int n, int m) {
    return n-m;
}

typedef int (*fptr_operation)(int, int);

int compute(fptr_operation op, int n, int m) {
    return op(n, m);
}

int main() {
    int n = 5;
    int m= 4;

    printf("Adding n and m: %d\n", compute(add, n, m));
    printf("Subtaacitng m from n: %d\n", compute(sub, n, m));


    return 0;
}
