#include <stdio.h>
#include <string.h>

int main() {
    char n1[5];
    char n2[5];
    
    // Will only copy first 4 chracters and then 5th would a NUL chracter
    snprintf(n2, sizeof(n2), "%s", "Bhaskar");

    printf("%s\n", n2);

    //Will give warning during compilation
    // Will crash during runtime
    strcpy(n1, "Bhaskar");

    return 0;
}

