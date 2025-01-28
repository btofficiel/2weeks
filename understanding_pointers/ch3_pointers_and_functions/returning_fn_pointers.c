#include <stdio.h>

int add(int n, int m) {
    return n+m;
}

int sub(int n, int m) {
    return n-m;
}

typedef int (*fptr_operation)(int, int);

// Returns a Function pointer based on opcode
fptr_operation select(char opcode) {
    switch(opcode) {
        case '+': return add;
        default: return sub;
    }
}

int evaluate(char opcode, int n, int m) {
    fptr_operation op = select(opcode);
    return op(n, m);
}

int main() {
    int n = 5;
    int m= 4;

    printf("Adding n and m: %d\n", evaluate('+', n, m));
    printf("Subtaacitng m from n: %d\n", evaluate('-', n, m));


    return 0;
}
