### <a name="Rf-range"></a>F.24: Use a `span<T>` or a `span_p<T>` to designate a half-open sequence

##### Reason

Informal/non-explicit ranges are a source of errors.

##### Example

```cpp
X* find(span<X> r, const X& v);    // find v in r

vector<X> vec;
// ...
auto p = find({vec.begin(), vec.end()}, X{});  // find X{} in vec

```
##### Note

Ranges are extremely common in C++ code. Typically, they are implicit and their correct use is very hard to ensure.
In particular, given a pair of arguments `(p, n)` designating an array \[`p`:`p+n`),
it is in general impossible to know if there really are `n` elements to access following `*p`.
`span<T>` and `span_p<T>` are simple helper classes designating a \[`p`:`q`) range and a range starting with `p` and ending with the first element for which a predicate is true, respectively.

##### Example

A `span` represents a range of elements, but how do we manipulate elements of that range?

```cpp
void f(span<int> s)
{
    // range traversal (guaranteed correct)
    for (int x : s) cout << x << '\n';

    // C-style traversal (potentially checked)
    for (int i = 0; i < s.size(); ++i) cout << s[i] << '\n';

    // random access (potentially checked)
    s[7] = 9;

    // extract pointers (potentially checked)
    std::sort(&s[0], &s[s.size() / 2]);
}

```
##### Note

A `span<T>` object does not own its elements and is so small that it can be passed by value.

Passing a `span` object as an argument is exactly as efficient as passing a pair of pointer arguments or passing a pointer and an integer count.

**See also**: [Support library](I-23-Guideline support library.md#S-gsl).

##### Enforcement

(Complex) Warn where accesses to pointer parameters are bounded by other parameters that are integral types and suggest they could use `span` instead.

