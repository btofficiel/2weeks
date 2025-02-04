- C is a horrifying language to write secure programs in
- always use * of pointers with the variable name
- Always initialised with NULLs
- Always always do bounds checks
- Best to use static analysis tools if possible.
- For strings even the std lib is vuln
- When doing ptr arthmetic always do it in places where you can be
sure its in contiguous memory allocation