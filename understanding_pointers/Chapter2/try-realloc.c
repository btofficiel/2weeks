#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
  char *p = (char *)malloc(10 * sizeof(char));
  if (p == NULL) {
    printf("Memory allocation failed\n");
    return 1;
  }
  strcpy(p, "Hello");
  printf("%s\n", p);
  p = (char *)realloc(p, 30 * sizeof(char));
  if (p == NULL) {
    printf("Memory allocation failed\n");
    return 1;
  }
  strcat(p, " World, Deba here!");
  printf("%s\n", p);
  p = (char *)realloc(p, 5 * sizeof(char));
  if (p == NULL) {
    printf("Memory allocation failed\n");
    return 1;
  }
  printf("%s\n", p); // note how the string is truncated but not of exact length
  free(p);
  return 0;
}
