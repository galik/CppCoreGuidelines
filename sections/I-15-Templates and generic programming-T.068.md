### <a name="Rt-cast"></a>T.68: Use `{}` rather than `()` within templates to avoid ambiguities

##### Reason

 `()` is vulnerable to grammar ambiguities.

##### Example

    template<typename T, typename U>
    void f(T t, U u)
    {
        T v1(x);    // is v1 a function of a variable?
        T v2 {x};   // variable
        auto x = T(u);  // construction or cast?
    }

    f(1, "asdf"); // bad: cast from const char* to int

##### Enforcement

* flag `()` initializers
* flag function-style casts


