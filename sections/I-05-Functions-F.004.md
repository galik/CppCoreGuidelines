### <a name="Rf-constexpr"></a>F.4: If a function may have to be evaluated at compile time, declare it `constexpr`

##### Reason

 `constexpr` is needed to tell the compiler to allow compile-time evaluation.

##### Example

The (in)famous factorial:

```cpp
constexpr int fac(int n)
{
    constexpr int max_exp = 17;      // constexpr enables max_exp to be used in Expects
    Expects(0 <= n && n < max_exp);  // prevent silliness and overflow
    int x = 1;
    for (int i = 2; i <= n; ++i) x *= i;
    return x;
}

```
This is C++14.
For C++11, use a recursive formulation of `fac()`.

##### Note

`constexpr` does not guarantee compile-time evaluation;
it just guarantees that the function can be evaluated at compile time for constant expression arguments if the programmer requires it or the compiler decides to do so to optimize.

```cpp
constexpr int min(int x, int y) { return x < y ? x : y; }

void test(int v)
{
    int m1 = min(-1, 2);            // probably compile-time evaluation
    constexpr int m2 = min(-1, 2);  // compile-time evaluation
    int m3 = min(-1, v);            // run-time evaluation
    constexpr int m4 = min(-1, v);  // error: cannot evaluate at compile-time
}

```
##### Note

`constexpr` functions are pure: they can have no side effects.

```cpp
int dcount = 0;
constexpr int double(int v)
{
    ++dcount;   // error: attempted side effect from constexpr function
    return v + v;
}

```
This is usually a very good thing.

When given a non-constant argument, a `constexpr` function can throw.
If you consider exiting by throwing a side-effect, a `constexpr` function isn't completely pure;
if not, this is not an issue.
??? A question for the committee: can a constructor for an exception thrown by a `constexpr` function modify state?
"No" would be a nice answer that matches most practice.

##### Note

Don't try to make all functions `constexpr`.
Most computation is best done at run time.

##### Note

Any API that may eventually depend on high-level runtime configuration or
business logic should not be made `constexpr`. Such customization can not be
evaluated by the compiler, and any `constexpr` functions that depended upon
that API would have to be refactored or drop `constexpr`.

##### Enforcement

Impossible and unnecessary.
The compiler gives an error if a non-`constexpr` function is called where a constant is required.

