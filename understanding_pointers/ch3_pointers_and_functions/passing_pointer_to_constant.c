#include <stdio.h>

void passAddressOfConstants(const int* num1) {
    *num1 = 100;
}

int main() {
    const int limit = 50;

    // Will throw an error
    // Using clang -> passing_pointer_to_constant.c:4:11: error: read-only variable is not assignable
    passAddressOfConstants(&limit);
    
    return 0;
}
