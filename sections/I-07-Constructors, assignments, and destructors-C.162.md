### <a name="Ro-equivalent"></a>C.162: Overload operations that are roughly equivalent

##### Reason

Having different names for logically equivalent operations on different argument types is confusing, leads to encoding type information in function names, and inhibits generic programming.

##### Example

Consider:

    void print(int a);
    void print(int a, int base);
    void print(const string&);

These three functions all print their arguments (appropriately). Conversely:

    void print_int(int a);
    void print_based(int a, int base);
    void print_string(const string&);

These three functions all print their arguments (appropriately). Adding to the name just introduced verbosity and inhibits generic code.

##### Enforcement

???

