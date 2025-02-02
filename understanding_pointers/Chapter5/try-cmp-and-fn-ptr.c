#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef int (*cmp_fn)(const char *, const char *);

int cmp_with_case(const char *s1, const char *s2) {
  return strcmp(s1, s2);
}

int cmp_without_case(const char *s1, const char *s2) {
  return strcasecmp(s1, s2);
}

void sort(char *arr[], int n, cmp_fn cmp) {
  for (int i = 0; i < n - 1; i++) {
    for (int j = i + 1; j < n; j++) {
      if (cmp(arr[i], arr[j]) > 0) {
        char *temp = arr[i];
        arr[i] = arr[j];
        arr[j] = temp;
      }
    }
  }
}

void display(char *arr[], int n) {
  for (int i = 0; i < n; i++) {
    printf("%s\n", arr[i]);
  }
}

int main() {
  char *arr[] = {"Bob", "Ted", "Carol", "Alice", "alice"};
  int n = sizeof(arr) / sizeof(arr[0]);
  sort(arr, n, cmp_without_case);
  display(arr, n);
}
