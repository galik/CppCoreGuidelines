### <a name="Rl-name-type"></a>NL.5: Don't encode type information in names

##### Rationale

If names reflect types rather than functionality, it becomes hard to change the types used to provide that functionality.
Also, if the type of a variable is changed, code using it will have to be modified.
Minimize unintentional conversions.

##### Example, bad

    void print_int(int i);
    void print_string(const char*);

    print_int(1);   // OK
    print_int(x);   // conversion to int if x is a double

##### Note

Names with types encoded are either verbose or cryptic.

    printS  // print a std::string
    prints  // print a C-style string
    printi  // print an int

PS. Hungarian notation is evil (at least in a strongly statically-typed language).

##### Note

Some styles distinguishes members from local variable, and/or from global variable.

    struct S {
        int m_;
        S(int m) :m_{abs(m)} { }
    };

This is not evil.

##### Note

Like C++, some styles distinguishes types from non-types.
For example, by capitalizing type names, but not the names of functions and variables.

    typename<typename T>
    class Hash_tbl {   // maps string to T
        // ...
    };

    Hash_tbl<int> index;

This is not evil.

