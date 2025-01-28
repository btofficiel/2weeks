#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int* allocateArray(int size, int value) {
int arr[size]; // use static to prevent this
for(int i=0; i<size; i++) {
arr[i] = value;
}
return arr;
}

int main() {
int *p = allocateArray(5, 10);
for(int i=0; i<5; i++) {
printf("%d ", p[i]);
}
return 0;
}