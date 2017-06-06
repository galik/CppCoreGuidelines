### <a name="Res-list"></a>ES.23: Prefer the `{}` initializer syntax

##### Reason

The rules for `{}` initialization are simpler, more general, less ambiguous, and safer than for other forms of initialization.

##### Example

```cpp
int x {f(99)};
vector<int> v = {1, 2, 3, 4, 5, 6};

```
##### Exception

For containers, there is a tradition for using `{...}` for a list of elements and `(...)` for sizes:

```cpp
vector<int> v1(10);    // vector of 10 elements with the default value 0
vector<int> v2 {10};   // vector of 1 element with the value 10

```
##### Note

`{}`-initializers do not allow narrowing conversions.

##### Example

```cpp
int x {7.9};   // error: narrowing
int y = 7.9;   // OK: y becomes 7. Hope for a compiler warning

```
##### Note

`{}` initialization can be used for all initialization; other forms of initialization can't:

```cpp
auto p = new vector<int> {1, 2, 3, 4, 5};   // initialized vector
D::D(int a, int b) :m{a, b} {   // member initializer (e.g., m might be a pair)
    // ...
};
X var {};   // initialize var to be empty
struct S {
    int m {7};   // default initializer for a member
    // ...
};

```
##### Note

Initialization of a variable declared using `auto` with a single value, e.g., `{v}`, had surprising results until C++17.
The C++17 rules are somewhat less surprising:

```cpp
auto x1 {7};        // x1 is an int with the value 7
auto x2 = {7};  // x2 is an initializer_list<int> with an element 7

auto x11 {7, 8};    // error: two initializers
auto x22 = {7, 8};  // x2 is an initializer_list<int> with elements 7 and 8

```
So use `={...}` if you really want an `initializer_list<T>`

```cpp
auto fib10 = {0, 1, 2, 3, 5, 8, 13, 21, 34, 55};   // fib10 is a list

```
##### Note

Old habits die hard, so this rule is hard to apply consistently, especially as there are so many cases where `=` is innocent.

##### Example

```cpp
template<typename T>
void f()
{
    T x1(1);    // T initialized with 1
    T x0();     // bad: function declaration (often a mistake)

    T y1 {1};   // T initialized with 1
    T y0 {};    // default initialized T
    // ...
}

```
**See also**: [Discussion](#???)

##### Enforcement

Tricky.

* Don't flag uses of `=` for simple initializers.
* Look for `=` after `auto` has been seen.

