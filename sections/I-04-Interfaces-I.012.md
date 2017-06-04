### <a name="Ri-nullptr"></a>I.12: Declare a pointer that must not be null as `not_null`

##### Reason

To help avoid dereferencing `nullptr` errors.
To improve performance by avoiding redundant checks for `nullptr`.

##### Example

    int length(const char* p);            // it is not clear whether length(nullptr) is valid

    length(nullptr);                      // OK?

    int length(not_null<const char*> p);  // better: we can assume that p cannot be nullptr

    int length(const char* p);            // we must assume that p can be nullptr

By stating the intent in source, implementers and tools can provide better diagnostics, such as finding some classes of errors through static analysis, and perform optimizations, such as removing branches and null tests.

##### Note

`not_null` is defined in the [guideline support library](I-23-Guideline%20support%20library.md#S-gsl).

##### Note

The assumption that the pointer to `char` pointed to a C-style string (a zero-terminated string of characters) was still implicit, and a potential source of confusion and errors. Use `czstring` in preference to `const char*`.

    // we can assume that p cannot be nullptr
    // we can assume that p points to a zero-terminated array of characters
    int length(not_null<zstring> p);

Note: `length()` is, of course, `std::strlen()` in disguise.

##### Enforcement

* (Simple) ((Foundation)) If a function checks a pointer parameter against `nullptr` before access, on all control-flow paths, then warn it should be declared `not_null`.
* (Complex) If a function with pointer return value ensures it is not `nullptr` on all return paths, then warn the return type should be declared `not_null`.

