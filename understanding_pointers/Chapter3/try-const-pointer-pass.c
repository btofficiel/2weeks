#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int printOut(const int *p) {
    printf("%d\n", *p);
    return 0;
}

int main() {
  int x = 10;
  printOut(&x);
  return 0;
}
