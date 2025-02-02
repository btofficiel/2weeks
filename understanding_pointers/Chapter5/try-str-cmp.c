#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
  char input[16];

  printf("Enter a string: ");
  scanf("%s", input);
  if (strcmp(input, "hello") == 0) {
    printf("You entered 'hello'\n");
  } else {
    printf("You entered something else\n");
  }
  return 0;
}