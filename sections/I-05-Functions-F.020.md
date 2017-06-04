### <a name="Rf-out"></a>F.20: For "out" output values, prefer return values to output parameters

##### Reason

A return value is self-documenting, whereas a `&` could be either in-out or out-only and is liable to be misused.

This includes large objects like standard containers that use implicit move operations for performance and to avoid explicit memory management.

If you have multiple values to return, [use a tuple](I-05-Functions-F.021.md#Rf-out-multi) or similar multi-member type.

##### Example

```cpp
// OK: return pointers to elements with the value x
vector<const int*> find_all(const vector<int>&, int x);

// Bad: place pointers to elements with value x in out
void find_all(const vector<int>&, vector<const int*>& out, int x);

```
##### Note

A `struct` of many (individually cheap-to-move) elements may be in aggregate expensive to move.

It is not recommended to return a `const` value.
Such older advice is now obsolete; it does not add value, and it interferes with move semantics.

```cpp
const vector<int> fct();    // bad: that "const" is more trouble than it is worth

vector<int> g(const vector<int>& vx)
{
    // ...
    f() = vx;   // prevented by the "const"
    // ...
    return f(); // expensive copy: move semantics suppressed by the "const"
}

```
The argument for adding `const` to a return value is that it prevents (very rare) accidental access to a temporary.
The argument against is prevents (very frequent) use of move semantics.

##### Exceptions

* For non-value types, such as types in an inheritance hierarchy, return the object by `unique_ptr` or `shared_ptr`.
* If a type is expensive to move (e.g., `array<BigPOD>`), consider allocating it on the free store and return a handle (e.g., `unique_ptr`), or passing it in a reference to non-`const` target object to fill (to be used as an out-parameter).
* To reuse an object that carries capacity (e.g., `std::string`, `std::vector`) across multiple calls to the function in an inner loop: [treat it as an in/out parameter and pass by reference](I-05-Functions-F.021.md#Rf-out-multi).

##### Example

```cpp
struct Package {      // exceptional case: expensive-to-move object
    char header[16];
    char load[2024 - 16];
};

Package fill();       // Bad: large return value
void fill(Package&);  // OK

int val();            // OK
void val(int&);       // Bad: Is val reading its argument

```
##### Enforcement

* Flag reference to non-`const` parameters that are not read before being written to and are a type that could be cheaply returned; they should be "out" return values.
* Flag returning a `const` value. To fix: Remove `const` to return a non-`const` value instead.

