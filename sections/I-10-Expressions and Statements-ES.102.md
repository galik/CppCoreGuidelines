### <a name="Res-signed"></a>ES.102: Use signed types for arithmetic

##### Reason

Because most arithmetic is assumed to be signed;
`x-y` yields a negative number when `y>x` except in the rare cases where you really want modulo arithmetic.

##### Example

Unsigned arithmetic can yield surprising results if you are not expecting it.
This is even more true for mixed signed and unsigned arithmetic.

    template<typename T, typename T2>
    T subtract(T x, T2 y)
    {
        return x-y;
    }

    void test()
    {
        int s = 5;
        unsigned int us = 5;
        cout << subtract(s, 7) << '\n';     // -2
        cout << subtract(us, 7u) << '\n';   // 4294967294
        cout << subtract(s, 7u) << '\n';    // -2
        cout << subtract(us, 7) << '\n';    // 4294967294
        cout << subtract(s, us+2) << '\n';  // -2
        cout << subtract(us, s+2) << '\n';  // 4294967294
    }

Here we have been very explicit about what's happening,
but if you had seen `us-(s+2)` or `s+=2; ... us-s`, would you reliably have suspected that the result would print as `4294967294`?

##### Exception

Use unsigned types if you really want modulo arithmetic - add
comments as necessary noting the reliance on overflow behavior, as such code
is going to be surprising for many programmers.

##### Example

The standard library uses unsigned types for subscripts.
The build-in array uses signed types for subscripts.
This makes surprises (and bugs) inevitable.

    int a[10];
    for (int i=0; i < 10; ++i) a[i]=i;
    vector<int> v(10);
    // compares signed to unsigned; some compilers warn
    for (int i=0; v.size() < 10; ++i) v[i]=i;

    int a2[-2];         // error: negative size

    // OK, but the number of ints (4294967294) is so large that we should get an exception
    vector<int> v2(-2);

##### Enforcement

* Flag mixed signed and unsigned arithmetic
* Flag results of unsigned arithmetic assigned to or printed as signed.
* Flag unsigned literals (e.g. `-2`) used as container subscripts.

