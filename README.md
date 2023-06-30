# orilang

Ori is a C-like programming language , without garbage collection or any other type of heavy - runtime. 

The main features are:
cutstom arena (region) allocators,that preallocates chunks of memory for futher use to reduce amount of syscalls.
Ease of refacting.
Fast compile time.

#Road to turing complete
   Lexing 
-> creation of AST
compiling / transpiling to c (?)
