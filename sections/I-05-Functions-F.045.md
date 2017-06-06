### <a name="Rf-return-ref-ref"></a>F.45: Don't return a `T&&`

##### Reason

It's asking to return a reference to a destroyed temporary object. A `&&` is a magnet for temporary objects. This is fine when the reference to the temporary is being passed "downward" to a callee, because the temporary is guaranteed to outlive the function call. (See [F.24](#Rf-pass-ref-ref) and [F.25](#Rf-pass-ref-move).) However, it's not fine when passing such a reference "upward" to a larger caller scope. See also ???.

For passthrough functions that pass in parameters (by ordinary reference or by perfect forwarding) and want to return values, use simple `auto` return type deduction (not `auto&&`).

##### Example, bad

If `F` returns by value, this function returns a reference to a temporary.

```cpp
template<class F>
auto&& wrapper(F f)
{
    log_call(typeid(f)); // or whatever instrumentation
    return f();
}

```
##### Example, good

Better:

```cpp
template<class F>
auto wrapper(F f)
{
    log_call(typeid(f)); // or whatever instrumentation
    return f();
}

```
##### Exception

`std::move` and `std::forward` do return `&&`, but they are just casts -- used by convention only in expression contexts where a reference to a temporary object is passed along within the same expression before the temporary is destroyed. We don't know of any other good examples of returning `&&`.

##### Enforcement

Flag any use of `&&` as a return type, except in `std::move` and `std::forward`.

