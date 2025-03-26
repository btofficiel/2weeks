#include <stdio.h>

int main() {
    int num = 0;
    int *pi = &num;
    printf("Address of pi: %d Value: %d\n",&pi, pi);
    printf("Address of pi: %x Value: %x\n",&pi, pi);
    printf("Address of pi: %o Value: %o\n",&pi, pi);
    printf("Address of pi: %p Value: %p\n",&pi, pi);
    return 0;
}
