### <a name="RT-operations"></a>T.21: Require a complete set of operations for a concept

##### Reason

Ease of comprehension.
Improved interoperability.
Helps implementers and maintainers.

##### Note

This is a specific variant of the general rule that [a concept must make semantic sense](I-15-Templates and generic programming-T.020.md#Rt-low).

##### Example, bad (using TS concepts)

```cpp
template<typename T> concept Subtractable = requires(T a, T, b) { a-b; };

```
This makes no semantic sense.
You need at least `+` to make `-` meaningful and useful.

Examples of complete sets are

* `Arithmetic`: `+`, `-`, `*`, `/`, `+=`, `-=`, `*=`, `/=`
* `Comparable`: `<`, `>`, `<=`, `>=`, `==`, `!=`

##### Note

This rule applies whether we use direct language support for concepts or not.
It is a general design rule that even applies to non-templates:

```cpp
class Minimal {
    // ...
};

bool operator==(const Minimal&, const Minimal&);
bool operator<(const Minimal&, const Minimal&);

Minimal operator+(const Minimal&, const Minimal&);
// no other operators

void f(const Minimal& x, const Minimal& y)
{
    if (!(x == y) { /* ... */ }     // OK
    if (x != y) { /* ... */ }       // surprise! error

    while (!(x < y)) { /* ... */ }  // OK
    while (x >= y) { /* ... */ }    // surprise! error

    x = x + y;        // OK
    x += y;             // surprise! error
}

```
This is minimal, but surprising and constraining for users.
It could even be less efficient.

The rule supports the view that a concept should reflect a (mathematically) coherent set of operations.

##### Example

```cpp
class Convenient {
    // ...
};

bool operator==(const Convenient&, const Convenient&);
bool operator<(const Convenient&, const Convenient&);
// ... and the other comparison operators ...

Minimal operator+(const Convenient&, const Convenient&);
// .. and the other arithmetic operators ...

void f(const Convenient& x, const Convenient& y)
{
    if (!(x == y) { /* ... */ }     // OK
    if (x != y) { /* ... */ }       // OK

    while (!(x < y)) { /* ... */ }  // OK
    while (x >= y) { /* ... */ }    // OK

    x = x + y;     // OK
    x += y;      // OK
}

```
It can be a nuisance to define all operators, but not hard.
Ideally, that rule should be language supported by giving you comparison operators by default.

##### Enforcement

* Flag classes the support "odd" subsets of a set of operators, e.g., `==` but not `!=` or `+` but not `-`.
  Yes, `std::string` is "odd", but it's too late to change that.


