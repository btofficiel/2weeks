- Program stack is the area basically for basically handling
the execution of functions
- Stack frames aka activation frames aka activation records
- The frames grow "upward"
- Heap tends to grow "downward" (generally)
- Stack frames store the following imp stuff
return address, local data ie local variables, parameters, stack
and base pointer (doesnt matter)
- Parameters are pushed in opp order of decl (obv stack)
- Constant pointer parameters good idea to avoid mishandling
- Several problems can happen when returning a pointer:
  - uninitialized ptr
  - invalid ptr
  - ptr to a local
  - not freeing
- static variable can restrict to fn scope but allocate outside stack frame.
- Weird syntax of declaring function pointers
- Dont cast into void* can be wrong
