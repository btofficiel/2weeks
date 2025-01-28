#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void safeFree(void **pp) {
    if(pp != NULL && *pp != NULL) {
        free(*pp);
        *pp = NULL;
    }
}

#define FREE(p) safeFree((void**)&(p))

int main() {
    int *p = (int*)malloc(sizeof(int));
    *p = 10;
    printf("%d\n", *p);
    FREE(p);
    if(p == NULL) {
        printf("p is successfully nullified\n");
    }
    return 0;
}
