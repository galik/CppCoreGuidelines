### <a name="Rf-in"></a>F.16: For "in" parameters, pass cheaply-copied types by value and others by reference to `const`

##### Reason

Both let the caller know that a function will not modify the argument, and both allow initialization by rvalues.

What is "cheap to copy" depends on the machine architecture, but two or three words (doubles, pointers, references) are usually best passed by value.
When copying is cheap, nothing beats the simplicity and safety of copying, and for small objects (up to two or three words) it is also faster than passing by reference because it does not require an extra indirection to access from the function.

##### Example

```cpp
void f1(const string& s);  // OK: pass by reference to const; always cheap

void f2(string s);         // bad: potentially expensive

void f3(int x);            // OK: Unbeatable

void f4(const int& x);     // bad: overhead on access in f4()

```
For advanced uses (only), where you really need to optimize for rvalues passed to "input-only" parameters:

* If the function is going to unconditionally move from the argument, take it by `&&`. See [F.18](I-05-Functions-F.018.md#Rf-consume).
* If the function is going to keep a copy of the argument, in addition to passing by `const&` (for lvalues),
  add an overload that passes the parameter by `&&` (for rvalues) and in the body `std::move`s it to its destination. Essentially this overloads a "consume"; see [F.18](I-05-Functions-F.018.md#Rf-consume).
* In special cases, such as multiple "input + copy" parameters, consider using perfect forwarding. See [F.19](I-05-Functions-F.019.md#Rf-forward).

##### Example

```cpp
int multiply(int, int); // just input ints, pass by value

// suffix is input-only but not as cheap as an int, pass by const&
string& concatenate(string&, const string& suffix);

void sink(unique_ptr<widget>);  // input only, and consumes the widget

```
Avoid "esoteric techniques" such as:

* Passing arguments as `T&&` "for efficiency".
  Most rumors about performance advantages from passing by `&&` are false or brittle (but see [F.25](#Rf-pass-ref-move).)
* Returning `const T&` from assignments and similar operations (see [F.47](I-05-Functions-F.047.md#Rf-assignment-op).)

##### Example

Assuming that `Matrix` has move operations (possibly by keeping its elements in a `std::vector`):

```cpp
Matrix operator+(const Matrix& a, const Matrix& b)
{
    Matrix res;
    // ... fill res with the sum ...
    return res;
}

Matrix x = m1 + m2;  // move constructor

y = m3 + m3;         // move assignment

```
##### Notes

The return value optimization doesn't handle the assignment case, but the move assignment does.

A reference may be assumed to refer to a valid object (language rule).
There is no (legitimate) "null reference."
If you need the notion of an optional value, use a pointer, `std::optional`, or a special value used to denote "no value."

##### Enforcement

* (Simple) ((Foundation)) Warn when a parameter being passed by value has a size greater than `4 * sizeof(int)`.
  Suggest using a reference to `const` instead.
* (Simple) ((Foundation)) Warn when a `const` parameter being passed by reference has a size less than `3 * sizeof(int)`. Suggest passing by value instead.
* (Simple) ((Foundation)) Warn when a `const` parameter being passed by reference is `move`d.

