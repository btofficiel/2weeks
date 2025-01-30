#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void printJaggedArray(int *arr[]) {
  int** curr = arr;
  while(*curr != NULL) {
    int* innerCurr = *curr;
    while(*innerCurr != -1) {
      printf("%d ", *innerCurr);
      innerCurr++;
    }
    printf("\n");
    curr++;
  }
}

int main() {
  int (*arr[4])[] = {
    (int[]){1, 2, 3, -1},
    (int[]){4, 5, -1}, // -1 to know when to stop
    (int[]){6, -1},
    NULL // This is important to know when to stop
    // note that its possible to put a wrong value in the length of the array
    // and the compiler wouldnt notice or stop you try setting
    // 4 to 3 and see what happens
  };

  printJaggedArray((int**)arr);
  return 0;
}