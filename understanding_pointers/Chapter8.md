- Casting pointers can be useful in embedded applications for casting
arb addresses where special values may be found
- Accessing the DMA is interesting need to investigate more
- Can access hardware ports using pointer casting
- Strict aliasing good dont mess with it turning off strict aliasing generally
a sign of bad memory access patterns
- Threads and pointers massive footgun
- Callbacks implemented as function pointers
