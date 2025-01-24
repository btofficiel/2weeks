#include <stdio.h>
#include <stdlib.h>

int main() {
    char *pc = (char*) malloc(6);
    for(int i=0;i<6;i++){
        *pc[i] = 0;
    }

    return 0;
}
