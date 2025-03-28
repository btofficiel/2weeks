#include <stdio.h>

void threadsafe_reentrant_reverse_string(char *in);

int main() {
    char in[100] = "stressed";
    threadsafe_reentrant_reverse_string(in);
    printf("Reversed stressed: %s\n", in);
    return 0;
}

void threadsafe_reentrant_reverse_string(char *in) {
    char buf[100];

    int size=0, i=0, j=0;

    while(in[size] != '\0' && size != 100) {
        size++;
    }

    for(i=size-1;i >-1;i--) {
        buf[j++] = in[i];
    }

    buf[j] = '\0';

    for(i=0;i<size+1;i++) {
        in[i] = buf[i];
    }
}
