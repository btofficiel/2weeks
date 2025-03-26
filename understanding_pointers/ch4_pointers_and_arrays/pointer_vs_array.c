int main() {
    int vector[3] = {1,2,3};

    int *pv = vector;

    pv = vector + 1;
    // An address asigned to an array cannot be changed.
    // We cannot modify vector's base address
    // We can only modify content within an array
    // This will throw an error
    // Using clang -> pointer_vs_array.c:7:12: error: array type 'int[3]' is not assignable
    vector = vector + 1;

    return 0;
}
