### <a name="Res-name-one"></a>ES.10: Declare one name (only) per declaration

##### Reason

One-declaration-per line increases readability and avoids mistakes related to
the C/C++ grammar. It also leaves room for a more descriptive end-of-line
comment.

##### Example, bad

    char *p, c, a[7], *pp[7], **aa[10];   // yuck!

##### Exception

A function declaration can contain several function argument declarations.

##### Exception

A structured binding (C++17) is specifically designed to introduce several variables:

    auto [iter, inserted] = m.insert_or_assign(k, val);
    if (inserted) { /* new entry was inserted */ }

##### Example

    template <class InputIterator, class Predicate>
    bool any_of(InputIterator first, InputIterator last, Predicate pred);

or better using concepts:

    bool any_of(InputIterator first, InputIterator last, Predicate pred);

##### Example

    double scalbn(double x, int n);   // OK: x * pow(FLT_RADIX, n); FLT_RADIX is usually 2

or:

    double scalbn(    // better: x * pow(FLT_RADIX, n); FLT_RADIX is usually 2
        double x,     // base value
        int n         // exponent
    );

or:

    // better: base * pow(FLT_RADIX, exponent); FLT_RADIX is usually 2
    double scalbn(double base, int exponent);

##### Example

    int a = 7, b = 9, c, d = 10, e = 3;

In a long list of declarators is is easy to overlook an uninitialized variable.

##### Enforcement

Flag variable and constant declarations with multiple declarators (e.g., `int* p, q;`)

