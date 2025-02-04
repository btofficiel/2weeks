- Typedefs generally used for struct declaration
- Pointer to struct requires -> notation to access
- Structs are generally allocated with padding
- Warning pointers in a structure are not allocated at structure allocation
- Having pointers in a struct now you have to be careful when deallocating
because you can have pointers lying around and cause memory leak
- Use pools to avoid overheads
- Checkout the linked list trial example in chapter folder