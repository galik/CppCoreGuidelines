### <a name="Ro-custom"></a>C.165: Use `using` for customization points

##### Reason

To find function objects and functions defined in a separate namespace to "customize" a common function.

##### Example

Consider `swap`. It is a general (standard library) function with a definition that will work for just about any type.
However, it is desirable to define specific `swap()`s for specific types.
For example, the general `swap()` will copy the elements of two `vector`s being swapped, whereas a good specific implementation will not copy elements at all.

```cpp
namespace N {
    My_type X { /* ... */ };
    void swap(X&, X&);   // optimized swap for N::X
    // ...
}

void f1(N::X& a, N::X& b)
{
    std::swap(a, b);   // probably not what we wanted: calls std::swap()
}

```
The `std::swap()` in `f1()` does exactly what we asked it to do: it calls the `swap()` in namespace `std`.
Unfortunately, that's probably not what we wanted.
How do we get `N::X` considered?

```cpp
void f2(N::X& a, N::X& b)
{
    swap(a, b);   // calls N::swap
}

```
But that may not be what we wanted for generic code.
There, we typically want the specific function if it exists and the general function if not.
This is done by including the general function in the lookup for the function:

```cpp
void f3(N::X& a, N::X& b)
{
    using std::swap;  // make std::swap available
    swap(a, b);        // calls N::swap if it exists, otherwise std::swap
}

```
##### Enforcement

Unlikely, except for known customization points, such as `swap`.
The problem is that the unqualified and qualified lookups both have uses.

