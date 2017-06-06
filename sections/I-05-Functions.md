# <a name="S-functions"></a>F: Functions

A function specifies an action or a computation that takes the system from one consistent state to the next. It is the fundamental building block of programs.

It should be possible to name a function meaningfully, to specify the requirements of its argument, and clearly state the relationship between the arguments and the result. An implementation is not a specification. Try to think about what a function does as well as about how it does it.
Functions are the most critical part in most interfaces, so see the interface rules.

Function rule summary:

Function definition rules:

* [F.1: "Package" meaningful operations as carefully named functions](I-05-Functions-F.001.md#Rf-package)
* [F.2: A function should perform a single logical operation](I-05-Functions-F.002.md#Rf-logical)
* [F.3: Keep functions short and simple](I-05-Functions-F.003.md#Rf-single)
* [F.4: If a function may have to be evaluated at compile time, declare it `constexpr`](I-05-Functions-F.004.md#Rf-constexpr)
* [F.5: If a function is very small and time-critical, declare it inline](I-05-Functions-F.005.md#Rf-inline)
* [F.6: If your function may not throw, declare it `noexcept`](I-05-Functions-F.006.md#Rf-noexcept)
* [F.7: For general use, take `T*` or `T&` arguments rather than smart pointers](I-05-Functions-F.007.md#Rf-smart)
* [F.8: Prefer pure functions](I-05-Functions-F.008.md#Rf-pure)
* [F.9: Unused parameters should be unnamed](I-05-Functions-F.009.md#Rf-unused)

Parameter passing expression rules:

* [F.15: Prefer simple and conventional ways of passing information](I-05-Functions-F.015.md#Rf-conventional)
* [F.16: For "in" parameters, pass cheaply-copied types by value and others by reference to `const`](I-05-Functions-F.016.md#Rf-in)
* [F.17: For "in-out" parameters, pass by reference to non-`const`](I-05-Functions-F.017.md#Rf-inout)
* [F.18: For "consume" parameters, pass by `X&&` and `std::move` the parameter](I-05-Functions-F.018.md#Rf-consume)
* [F.19: For "forward" parameters, pass by `TP&&` and only `std::forward` the parameter](I-05-Functions-F.019.md#Rf-forward)
* [F.20: For "out" output values, prefer return values to output parameters](I-05-Functions-F.020.md#Rf-out)
* [F.21: To return multiple "out" values, prefer returning a tuple or struct](I-05-Functions-F.021.md#Rf-out-multi)
* [F.60: Prefer `T*` over `T&` when "no argument" is a valid option](I-05-Functions-F.060.md#Rf-ptr-ref)

Parameter passing semantic rules:

* [F.22: Use `T*` or `owner<T*>` or a smart pointer to designate a single object](I-05-Functions-F.022.md#Rf-ptr)
* [F.23: Use a `not_null<T>` to indicate "null" is not a valid value](I-05-Functions-F.023.md#Rf-nullptr)
* [F.24: Use a `span<T>` or a `span_p<T>` to designate a half-open sequence](I-05-Functions-F.024.md#Rf-range)
* [F.25: Use a `zstring` or a `not_null<zstring>` to designate a C-style string](I-05-Functions-F.025.md#Rf-zstring)
* [F.26: Use a `unique_ptr<T>` to transfer ownership where a pointer is needed](I-05-Functions-F.026.md#Rf-unique_ptr)
* [F.27: Use a `shared_ptr<T>` to share ownership](I-05-Functions-F.027.md#Rf-shared_ptr)

Value return semantic rules:

* [F.42: Return a `T*` to indicate a position (only)](I-05-Functions-F.042.md#Rf-return-ptr)
* [F.43: Never (directly or indirectly) return a pointer or a reference to a local object](I-05-Functions-F.043.md#Rf-dangle)
* [F.44: Return a `T&` when copy is undesirable and "returning no object" isn't an option](I-05-Functions-F.044.md#Rf-return-ref)
* [F.45: Don't return a `T&&`](I-05-Functions-F.045.md#Rf-return-ref-ref)
* [F.46: `int` is the return type for `main()`](I-05-Functions-F.046.md#Rf-main)
* [F.47: Return `T&` from assignment operators.](I-05-Functions-F.047.md#Rf-assignment-op)

Other function rules:

* [F.50: Use a lambda when a function won't do (to capture local variables, or to write a local function)](I-05-Functions-F.050.md#Rf-capture-vs-overload)
* [F.51: Where there is a choice, prefer default arguments over overloading](I-05-Functions-F.051.md#Rf-default-args)
* [F.52: Prefer capturing by reference in lambdas that will be used locally, including passed to algorithms](I-05-Functions-F.052.md#Rf-reference-capture)
* [F.53: Avoid capturing by reference in lambdas that will be used nonlocally, including returned, stored on the heap, or passed to another thread](I-05-Functions-F.053.md#Rf-value-capture)
* [F.54: If you capture `this`, capture all variables explicitly (no default capture)](I-05-Functions-F.054.md#Rf-this-capture)
* [F.55: Don't use `va_arg` arguments](I-05-Functions-F.055.md#F-varargs)

Functions have strong similarities to lambdas and function objects so see also Section ???.

## <a name="SS-fct-def"></a>F.def: Function definitions

A function definition is a function declaration that also specifies the function's implementation, the function body.

