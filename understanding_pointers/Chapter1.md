# Learnings

- Basic syntax stuff * and deref &
- Null is an interesting area lot of null stuff
  - The null pointer constant is implementation defined but generally its
  (void*)0 and two null pointers = and signify pointing to "nothing"
  - Warn null pointer and uninitialised pointer different things
  - The ASCII nul is byte of 0s
- void pointer basically points to any datatype same alignas char
- Two void pointers are never equal
- Static and global pointers autoinitialised NULL
- Memory model table is interesting to be studied in greater detail
- ptrdiff_t for pointer arith
- uintptr_t and intptr_t for actually storing the addresses
- used for portability and safety
- Pointers allow for basic arithmetic stuff with +, - being useful
  - + generally for accessing contiguous mem like in array
  - minus could be used to do things like getting array length
- Pointers to Constants note the helpful diagram Figure 1-12
- Constant pointer is one where pointer is constant but the memory being pointed
  to can be updated
- More deranged stuff about constant pointers to constants note the diagrams
  Figure 1-14 for understanding
- TODO: try out constant pointers.
