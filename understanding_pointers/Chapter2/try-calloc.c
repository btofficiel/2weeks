#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    int *p = (int *)calloc(1, sizeof(int));
    *p = 10;
    if (p == NULL) {
        printf("Memory allocation failed\n");
        return 1;
    }
    printf("%d\n", *p);
    free(p); // not freeing = mem leak
    int *parr = (int *)calloc(5, sizeof(int));
    for (int i = 0; i < 5; i++) {
        printf("%d ", parr[i]);
    }
    return 0;
}