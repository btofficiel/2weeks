#include <stdio.h>
#include <stdlib.h>

int main() {
    char *chunk;
    // Infinite loop goes brrr....
    // If you keep it running it leads to -> zsh: killed     ./leak.o
    while(1) {
        chunk = (char*) malloc(1000000);
        printf("Allocating\n");
    }
    
    return 0;
}
