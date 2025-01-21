#include <stdio.h>

int main() {
    int num = 50;

    int *pi = &num;

    //Compiler implicitly converts it to NULL
    pi = 0;

    pi = NULL;

    pi = 100; //Syntax error

    pi = num; //Syntax error
              
    return 0;
}
