### <a name="Rsl-bounds"></a>SL.con.3: Avoid bounds errors

##### Reason

Read or write beyond an allocated range of elements typically leads to bad errors, wrong results, crashes, and security violations.

##### Note

The standard-library functions that apply to ranges of elements all have (or could have) bounds-safe overloads that take `span`.
Standard types such as `vector` can be modified to perform bounds-checks under the bounds profile (in a compatible way, such as by adding contracts), or used with `at()`.

Ideally, the in-bounds guarantee should be statically enforced.
For example:

* a range-`for` cannot loop beyond the range of the container to which it is applied
* a `v.begin(),v.end()` is easily determined to be bounds safe

Such loops are as fast as any unchecked/unsafe equivalent.

Often a simple pre-check can eliminate the need for checking of individual indices.
For example

* for `v.begin(),v.begin()+i` the `i` can easily be checked against `v.size()`

Such loops can be much faster than individually checked element accesses.

##### Example, bad

```cpp
void f()
{
    array<int, 10> a, b;
    memset(a.data(), 0, 10);         // BAD, and contains a length error (length = 10 * sizeof(int))
    memcmp(a.data(), b.data(), 10);  // BAD, and contains a length error (length = 10 * sizeof(int))
}

```
Also, `std::array<>::fill()` or `std::fill()` or even an empty initializer are better candidate than `memset()`.

##### Example, good

```cpp
void f()
{
    array<int, 10> a, b, c{};       // c is initialized to zero
    a.fill(0);
    fill(b.begin(), b.end(), 0);    // std::fill()
    fill(b, 0);                     // std::fill() + Ranges TS

    if ( a == b ) {
      // ...
    }
}

```
##### Example

If code is using an unmodified standard library, then there are still workarounds that enable use of `std::array` and `std::vector` in a bounds-safe manner. Code can call the `.at()` member function on each class, which will result in an `std::out_of_range` exception being thrown. Alternatively, code can call the `at()` free function, which will result in fail-fast (or a customized action) on a bounds violation.

```cpp
void f(std::vector<int>& v, std::array<int, 12> a, int i)
{
    v[0] = a[0];        // BAD
    v.at(0) = a[0];     // OK (alternative 1)
    at(v, 0) = a[0];    // OK (alternative 2)

    v.at(0) = a[i];     // BAD
    v.at(0) = a.at(i);  // OK (alternative 1)
    v.at(0) = at(a, i); // OK (alternative 2)
}

```
##### Enforcement

* Issue a diagnostic for any call to a standard library function that is not bounds-checked.
??? insert link to a list of banned functions

This rule is part of the [bounds profile](I-22-Profiles.md#SS-bounds).

**TODO Notes**:

* Impact on the standard library will require close coordination with WG21, if only to ensure compatibility even if never standardized.
* We are considering specifying bounds-safe overloads for stdlib (especially C stdlib) functions like `memcmp` and shipping them in the GSL.
* For existing stdlib functions and types like `vector` that are not fully bounds-checked, the goal is for these features to be bounds-checked when called from code with the bounds profile on, and unchecked when called from legacy code, possibly using contracts (concurrently being proposed by several WG21 members).



## <a name="SS-string"></a>SL.str: String

Text manipulation is a huge topic.
`std::string` doesn't cover all of it.
This section primarily tries to clarify `std::string`'s relation to `char*`, `zstring`, `string_view`, and `gsl::string_span`.
The important issue of non-ASCII character sets and encodings (e.g., `wchar_t`, Unicode, and UTF-8) will be covered elsewhere.

See also [regular expressions](I-18-The Standard Library-SL.io.050.md#SS-regex).

Here, we use "sequence of characters" or "string" to refer to a sequence of characters meant to be read as text (somehow, eventually).
We don't consider 

String summary:

* [SL.str.1: Use `std::string` to own character sequences](I-18-The Standard Library-SL.str.001.md#Rstr-string)
* [SL.str.2: Use `std::string_view` or `gsl::string_span` to refer to character sequences](I-18-The Standard Library-SL.str.002.md#Rstr-view)
* [SL.str.3: Use `zstring` or `czstring` to refer to a C-style, zero-terminated, sequence of characters](I-18-The Standard Library-SL.str.003.md#Rstr-zstring)
* [SL.str.4: Use `char*` to refer to a single character](I-18-The Standard Library-SL.str.004.md#Rstr-char*)
* [Sl.str.5: Use `std::byte` to refer to byte values that do not necessarily represent characters](I-18-The Standard Library-Sl.str.005.md#Rstr-byte)

* [Sl.str.10: Use `std::string` when you need to perform locale-sensitive string operations](I-18-The Standard Library-Sl.str.010.md#Rstr-locale)
* [Sl.str.11: Use `gsl::string_span` rather than `std::string_view` when you need to mutate a string](I-18-The Standard Library-Sl.str.011.md#Rstr-span)
* [Sl.str.12: Use the `s` suffix for string literals meant to be standard-library `string`s](I-18-The Standard Library-Sl.str.012.md#Rstr-s)

See also

* [F.24 span](I-05-Functions-F.024.md#Rf-range)
* [F.25 zstring](I-05-Functions-F.025.md#Rf-zstring)


