### <a name="Rconst-fct"></a>Con.2: By default, make member functions `const`

##### Reason

A member function should be marked `const` unless it changes the object's observable state.
This gives a more precise statement of design intent, better readability, more errors caught by the compiler, and sometimes more optimization opportunities.

##### Example; bad

```cpp
class Point {
    int x, y;
public:
    int getx() { return x; }    // BAD, should be const as it doesn't modify the object's state
    // ...
};

void f(const Point& pt) {
    int x = pt.getx();          // ERROR, doesn't compile because getx was not marked const
}

```
##### Note

It is not inherently bad to pass a pointer or reference to non-const,
but that should be done only when the called function is supposed to modify the object.
A reader of code must assume that a function that takes a "plain" `T*` or `T&` will modify the object referred to.
If it doesn't now, it might do so later without forcing recompilation.

##### Note

There are code/libraries that are offer functions that declare a`T*` even though
those function do not modify that `T`.
This is a problem for people modernizing code.
You can

* update the library to be `const`-correct; preferred long-term solution
* "cast away `const`"; [best avoided](I-10-Expressions%20and%20Statements-ES.050.md#Res-casts-const)
* provide a wrapper function

Example:

```cpp
void f(int* p);   // old code: f() does not modify `*p`
void f(const int* p) { f(const_cast<int*>(p); } // wrapper

```
Note that this wrapper solution is a patch that should be used only when the declaration of `f()` cannot be be modified,
e.g. because it is in a library that you cannot modify.

##### Note

A `const` member function can modify the value of an object that is `mutable` or accessed through a pointer member.
A common use is to maintain a cache rather than repeatedly do a complicated computation.
For example, here is a `Date` that caches (mnemonizes) its string representation to simplify repeated uses:

```cpp
class Date {
public:
    // ...
    const string& string_ref() const
    {
        if (string_val == "") compute_string_rep();
        return string_val;
    }
    // ...
private:
    void compute_string_rep() const;    // compute string representation and place it in string_val
    mutable string string_val;
    // ...
};

```
Another way of saying this is that `const`ness is not transitive.
It is possible for a `const` member function to change the value of `mutable` members and the value of objects accessed
through non-`const` pointers.
It is the job of the class to ensure such mutation is done only when it makes sense according to the semantics (invariants)
it offers to its users.

See also [PIMPL](#???).

##### Enforcement

* Flag a member function that is not marked `const`, but that does not perform a non-`const` operation on any member variable.

