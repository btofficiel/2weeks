#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int add(int a, int b) {
    return a + b;
}

int subtract(int a, int b) {
    return a - b;
}

typedef int (*binop_fn)(int, int);

binop_fn getBinOp(char op) {
    switch(op) {
        case '+': return add;
        case '-': return subtract;
        default: return NULL;
    }
}

int main() {
    binop_fn binop = getBinOp('+');
    if(binop != NULL) {
        printf("%d\n", binop(10, 20));
    }
    binop_fn binop2 = getBinOp('-');
    if(binop2 != NULL) {
        printf("%d\n", binop2(10, 20));
    }
    return 0;
}


