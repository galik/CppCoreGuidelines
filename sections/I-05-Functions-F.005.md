### <a name="Rf-inline"></a>F.5: If a function is very small and time-critical, declare it `inline`

##### Reason

Some optimizers are good at inlining without hints from the programmer, but don't rely on it.
Measure! Over the last 40 years or so, we have been promised compilers that can inline better than humans without hints from humans.
We are still waiting.
Specifying `inline` encourages the compiler to do a better job.

##### Example

```cpp
inline string cat(const string& s, const string& s2) { return s + s2; }

```
##### Exception

Do not put an `inline` function in what is meant to be a stable interface unless you are certain that it will not change.
An inline function is part of the ABI.

##### Note

`constexpr` implies `inline`.

##### Note

Member functions defined in-class are `inline` by default.

##### Exception

Template functions (incl. template member functions) must be in headers and therefore inline.

##### Enforcement

Flag `inline` functions that are more than three statements and could have been declared out of line (such as class member functions).

