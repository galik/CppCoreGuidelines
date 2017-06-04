### <a name="Rio-streams"></a>SL.io.3: Prefer `iostream`s for I/O

##### Reason

`iostream`s are safe, flexible, and extensible.

##### Example

    // write a complex number:
    complex<double> z{ 3, 4 };
    cout << z << '\n';

`complex` is a user defined type and its I/O is defined without modifying the `iostream` library.

##### Example

    // read a file of complex numbers:
    for (complex<double> z; cin >> z; )
        v.push_back(z);

##### Exception

??? performance ???

##### Discussion: `iostream`s vs. the `printf()` family

It is often (and often correctly) pointed out that the `printf()` family has two advantages compared to `iostream`s:
flexibility of formatting and performance.
This has to be weighed against `iostream`s advantages of extensibility to handle user-defined types, resilient against security violations,
implicit memory management, and `locale` handling.

If you need I/O performance, you can almost always do better than `printf()`.

`gets()` `scanf()` using `s`, and `printf()` using `%s` are security hazards (vulnerable to buffer overflow and generally error-prone).
In C11, they are replaced by `gets_s()`, `scanf_s()`, and `printf_s()` as safer alternatives, but they are still not type safe.

##### Enforcement

Optionally flag `<cstdio>` and `<stdio.h>`.

