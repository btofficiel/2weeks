#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define RAII_CLEANUP_FUNC(vartype, dtor, fname)  \
    static inline void fname(vartype *v) { dtor(*v); printf("Cleanup success\n"); }

#define RAII_VARIABLE(vartype, varname, initval, fname) \
    vartype varname __attribute__((cleanup(fname))) = (initval)

RAII_CLEANUP_FUNC(char*, free, dtor_for_charstar)

int main() {
  RAII_VARIABLE(char*, name, (char*)malloc(32), dtor_for_charstar);
  strcpy(name, "Deba");
  printf("%s\n", name);
  {
    RAII_VARIABLE(char*, name2, (char*)malloc(32), dtor_for_charstar);
    strcpy(name2, "Deba2");
    printf("%s\n", name2);
  }
  {
    RAII_VARIABLE(char*, name3, (char*)malloc(32), dtor_for_charstar);
    strcpy(name3, "Deba3");
    printf("%s\n", name3);
  }
  return 0;
}