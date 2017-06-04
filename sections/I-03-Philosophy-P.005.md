### <a name="Rp-compile-time"></a>P.5: Prefer compile-time checking to run-time checking

##### Reason

Code clarity and performance.
You don't need to write error handlers for errors caught at compile time.

##### Example

    // Int is an alias used for integers
    int bits = 0;         // don't: avoidable code
    for (Int i = 1; i; i <<= 1)
        ++bits;
    if (bits < 32)
        cerr << "Int too small\n"

This example is easily simplified

    // Int is an alias used for integers
    static_assert(sizeof(Int) >= 4);    // do: compile-time check

##### Example

    void read(int* p, int n);   // read max n integers into *p

    int a[100];
    read(a, 1000);    // bad

better

    void read(span<int> r); // read into the range of integers r

    int a[100];
    read(a);        // better: let the compiler figure out the number of elements

**Alternative formulation**: Don't postpone to run time what can be done well at compile time.

##### Enforcement

* Look for pointer arguments.
* Look for run-time checks for range violations.

