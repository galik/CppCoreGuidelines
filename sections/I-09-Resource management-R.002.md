### <a name="Rr-use-ptr"></a>R.2: In interfaces, use raw pointers to denote individual objects (only)

##### Reason

Arrays are best represented by a container type (e.g., `vector` (owning)) or a `span` (non-owning).
Such containers and views hold sufficient information to do range checking.

##### Example, bad

```cpp
void f(int* p, int n)   // n is the number of elements in p[]
{
    // ...
    p[2] = 7;   // bad: subscript raw pointer
    // ...
}

```
The compiler does not read comments, and without reading other code you do not know whether `p` really points to `n` elements.
Use a `span` instead.

##### Example

```cpp
void g(int* p, int fmt)   // print *p using format #fmt
{
    // ... uses *p and p[0] only ...
}

```
##### Exception

C-style strings are passed as single pointers to a zero-terminated sequence of characters.
Use `zstring` rather than `char*` to indicate that you rely on that convention.

##### Note

Many current uses of pointers to a single element could be references.
However, where `nullptr` is a possible value, a reference may not be an reasonable alternative.

##### Enforcement

* Flag pointer arithmetic (including `++`) on a pointer that is not part of a container, view, or iterator.
  This rule would generate a huge number of false positives if applied to an older code base.
* Flag array names passed as simple pointers

