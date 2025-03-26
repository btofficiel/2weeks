#include <stdio.h>

int add(int n, int m) {
    return n+m;
}

int sub(int n, int m) {
    return n-m;
}

// Mapping each of first 128 ASCII characters to function
int (*operations[128])(int, int) = {NULL};

typedef int (*fptr_operation)(int, int);

void initialiseOperationsArray() {
    operations['+'] = add;
    operations['-'] = sub;
}

int evaluate(char opcode, int n, int m) {
    fptr_operation op = operations[opcode];
    return op(n, m);
}

int main() {
    int n = 5;
    int m= 4;

    initialiseOperationsArray();

    printf("Adding n and m: %d\n", evaluate('+', n, m));
    printf("Subtaacitng m from n: %d\n", evaluate('-', n, m));


    return 0;
}
