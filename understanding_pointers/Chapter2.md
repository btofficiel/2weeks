- Journey starts with memory leaks (basically skill issue)
- Common programmatic way of doing memory leaks is losing the og mem
address
- malloc dynamic memory allocation function
- cast the malloc generated pointer for safety and compaitbility
- It can be null
- Calloc is equal to malloc + memset 0
- Realloc used to reallocate a pointer, if more space req may allocate
right adj or in a diff location or if space req is less then the remaining space
may be reclaimed no gurantees
- free function for deallocating pointers
- Cannot detect double frees
- Dangling pointer when pointing to a memory location even after freeing see
example code
- Can especially cause issue with block statements.
- Best way it seems is to assign NULL to pointer after free
- RAII a great way to handling memory resources.
- Have written a very good example on raii check folder