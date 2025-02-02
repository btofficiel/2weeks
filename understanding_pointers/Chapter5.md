- Strings are an ascii sequence terminated by a NUL
- NUL = '\0'
- When a literal is used multiple times it maybe allocated in a literal
pool to prevent excess mem usage
- GCC is a terrible compiler that can allow messing with literals
- String comparison <0 if lexico precede > 0 if following eq 0 if eql
- Two pointers can point to the same str its called aliasing
- Strcat assumes the first string is large enough to consume the second into it
- Good idea to pass a const char* when passing strs
- Do not use static * when function is to use that pointer internally between
calls can overwrite
