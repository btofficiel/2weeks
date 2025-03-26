#include <stdio.h>
#include <signal.h>
#include <string.h>

int main() {

    char *t1 = "ERROR: ";
    char *t2 = "Not enough memory";
    
    // Trace trap error!
    strcat(t1, t2);

    printf("%s\n", t1);
    printf("%s\n", t2);

    return 0;
}

