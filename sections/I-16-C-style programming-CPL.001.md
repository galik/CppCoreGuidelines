### <a name="Rcpl-C"></a>CPL.1: Prefer C++ to C

##### Reason

C++ provides better type checking and more notational support.
It provides better support for high-level programming and often generates faster code.

##### Example

    char ch = 7;
    void* pv = &ch;
    int* pi = pv;   // not C++
    *pi = 999;      // overwrite sizeof(int) bytes near &ch

The rules for implicit casting to and from `void*` in C are subtle and unenforced.
In particular, this example violates a rule against converting to a type with stricter alignment.

##### Enforcement

Use a C++ compiler.

