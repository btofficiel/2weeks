#include <stdio.h>

int main() {
    char *names[] = {"Miller", "Jones", "Anderson"};
    /*
     * 'names' gives the base address of the array
     * Adding 1 to names points the pointer to second element of the array
     * Dereferrencing this i.e. *(names+1) gives pointer to the seconnd element which is Jones.
     * Adding 2 to that pointer it two positions forward to the letter 'n'.
     * Dereferrencing it i.e. *(*(names+1)+2) retrieves the character 'n'
     */
    printf("%c\n", *(*(names+1)+2));
    printf("%c\n", names[1][2]);
    return 0;
}
