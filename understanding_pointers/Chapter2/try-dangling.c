#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
  int *p = (int *)malloc(sizeof(int));
  *p = 10;
  if (p == NULL) {
    printf("Memory allocation failed\n");
    return 1;
  }
  printf("%d\n", *p);
  free(p);
  *p = 20; // dangling pointer can be overriden etc etc many things can go wrong
  printf("%d\n", *p);
  return 0;
}