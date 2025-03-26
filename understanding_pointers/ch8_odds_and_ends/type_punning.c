#include <stdio.h>
#include <string.h>

/* Definition from Qwen 2.5-Max
 *
 * Type punning is a technique in programming where you interpret or access the same memory location using different data types. It allows you to "reinterpret" the bits of one type as another type, effectively "punning" the original type into a new one. This can be useful in low-level programming, such as embedded systems, operating system kernels, or performance-critical applications.
 *
 */

typedef union _conversion {
    float fi;
    int i;
} Conversion;

int main() {
    // Via unions
    Conversion u;
    u.fi = 3.14f;
    int i = u.i;  // Access the same memory as an integer


    // Via memcpy
    float f = 3.14f;
    int i2;
    memcpy(&i2, &f, sizeof(f));  // Copy the bits of 'f' into 'i'

    // Via casting pointers
    float f2 = 3.14f;
    int i3 = *(int *)&f2;  // Reinterpret the bits of 'f' as an integer

    return 0;
}

