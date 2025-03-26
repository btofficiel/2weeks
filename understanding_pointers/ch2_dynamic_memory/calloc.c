#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(){
    // Allocates 5*4-byte (size of int)= 20 bytes
    // All of it contains zeros and no garbage values
    int *pi = calloc(5, sizeof(int));

    // Allocates memory using malloc
    // Initialising it with zero values using memset
    int *pi2 = malloc(5*sizeof(int));
    memset(pi2, 0, 5*sizeof(int));

    /*
     * A big difference between calloc and malloc with memset is that
     * calloc checks for integer overflow when multiplying num of elements and size of on element
     * while in case of malloc with memset it is upto the user
     */


    // Should print 0 for both
    printf("Value at pi: %d\n", *pi);
    printf("Value at pi2: %d\n", *pi2);

    return 0;
}
