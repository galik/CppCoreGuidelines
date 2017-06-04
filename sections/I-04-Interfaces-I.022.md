### <a name="Ri-global-init"></a>I.22: Avoid complex initialization of global objects

##### Reason

Complex initialization can lead to undefined order of execution.

##### Example

    // file1.c

    extern const X x;

    const Y y = f(x);   // read x; write y

    // file2.c

    extern const Y y;

    const X x = g(y);   // read y; write x

Since `x` and `y` are in different translation units the order of calls to `f()` and `g()` is undefined;
one will access an uninitialized `const`.
This shows that the order-of-initialization problem for global (namespace scope) objects is not limited to global *variables*.

##### Note

Order of initialization problems become particularly difficult to handle in concurrent code.
It is usually best to avoid global (namespace scope) objects altogether.

##### Enforcement

* Flag initializers of globals that call non-`constexpr` functions
* Flag initializers of globals that access `extern` objects

