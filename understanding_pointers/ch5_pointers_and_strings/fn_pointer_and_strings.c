#include <stdio.h>
#include <string.h>

int compare(const char* s1, const char* s2) {
    return strcmp(s1, s2);
}

typedef int (fptrOperation) (const char*, const char*);

void sort(char *arr[], size_t size, fptrOperation operation) {
    int swap = 1;

    while(swap) {
        swap = 0;
        for(int i=0;i<size-1;i++) {
            if(operation(arr[i], arr[i+1]) > 0) {
                swap = 1;
                char* tmp = arr[i];
                arr[i] = arr[i+1];
                arr[i+1] = tmp;
            }
        }
    }
}

int main() {
    char *names[] = {"Shashwat", "Bhaskar", "Pushp"};
    sort(names, 3, compare);

    for(int i=0;i<3;i++) {
        printf("%s\n", names[i]);
    }

    return 0;
}



