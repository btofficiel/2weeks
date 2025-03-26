#include <stdio.h>

int main() {
    int num = 5;
    int *pi = &num;

    printf("%p\n", *pi);

    // Since *p is an lvalue, it is modifiable;
    
    *pi = 200;

    //Since pi holds the address num, modifying dereferenced pi changes value of num
    printf("%d\n", num);

    return 0;
}
