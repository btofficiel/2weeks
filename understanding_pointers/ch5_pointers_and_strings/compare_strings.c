#include <stdio.h>
#include <string.h>

int main() {
    char s1[] = "Bhaskar";
    char s2[] = "Adarsh";

    printf("Should print 0: %d\n", strcmp(s1, s1));
    // Because ASCII value of A is lower than B
    printf("Should print -1: %d\n", strcmp(s2, s1));
    // Because ASCII value of B is higher than A
    printf("Should print 1: %d\n", strcmp(s1, s2));

    return 0;
}
