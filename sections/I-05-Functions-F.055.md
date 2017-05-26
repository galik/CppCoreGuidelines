### <a name="F-varargs"></a>F.55: Don't use `va_arg` arguments

##### Reason

Reading from a `va_arg` assumes that the correct type was actually passed.
Passing to varargs assumes the correct type will be read.
This is fragile because it cannot generally be enforced to be safe in the language and so relies on programmer discipline to get it right.

##### Example

```cpp
int sum(...) {
    // ...
    while (/*...*/)
        result += va_arg(list, int); // BAD, assumes it will be passed ints
    // ...
}

sum(3, 2); // ok
sum(3.14159, 2.71828); // BAD, undefined

template<class ...Args>
auto sum(Args... args) { // GOOD, and much more flexible
    return (... + args); // note: C++17 "fold expression"
}

sum(3, 2); // ok: 5
sum(3.14159, 2.71828); // ok: ~5.85987

```
##### Alternatives

* overloading
* variadic templates
* `variant` arguments
* `initializer_list` (homogeneous)

##### Note

Declaring a `...` parameter is sometimes useful for techniques that don't involve actual argument passing, notably to declare "take-anything" functions so as to disable "everything else" in an overload set or express a catchall case in a template metaprogram.

##### Enforcement

* Issue a diagnostic for using `va_list`, `va_start`, or `va_arg`.
* Issue a diagnostic for passing an argument to a vararg parameter of a function that does not offer an overload for a more specific type in the position of the vararg. To fix: Use a different function, or `[[suppress(types)]]`.

