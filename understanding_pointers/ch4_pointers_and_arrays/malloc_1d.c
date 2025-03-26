#include <stdio.h>
#include <stdlib.h>

int main() {
    int *pv = (int*) malloc(10*sizeof(int));
    int *pvp = (int*) malloc(10*sizeof(int));

    // Using array notation
    for(int i=0; i<10;i++) {
        pv[i] = i+1;
    }

    // Using pointer notation

    for(int i=0; i<10;i++) {
        // Point it to ith element and dereference it to set value
        *(pv+i) = i+1;
    }

    return 0;
}



    
