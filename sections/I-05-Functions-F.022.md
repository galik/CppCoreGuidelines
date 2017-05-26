### <a name="Rf-ptr"></a>F.22: Use `T*` or `owner<T*>` to designate a single object

##### Reason

Readability: it makes the meaning of a plain pointer clear.
Enables significant tool support.

##### Note

In traditional C and C++ code, plain `T*` is used for many weakly-related purposes, such as:

* Identify a (single) object (not to be deleted by this function)
* Point to an object allocated on the free store (and delete it later)
* Hold the `nullptr`
* Identify a C-style string (zero-terminated array of characters)
* Identify an array with a length specified separately
* Identify a location in an array

This makes it hard to understand what the code does and is supposed to do.
It complicates checking and tool support.

##### Example

```cpp
void use(int* p, int n, char* s, int* q)
{
    p[n - 1] = 666; // Bad: we don't know if p points to n elements;
                    // assume it does not or use span<int>
    cout << s;      // Bad: we don't know if that s points to a zero-terminated array of char;
                    // assume it does not or use zstring
    delete q;       // Bad: we don't know if *q is allocated on the free store;
                    // assume it does not or use owner
}

```
better

```cpp
void use2(span<int> p, zstring s, owner<int*> q)
{
    p[p.size() - 1] = 666; // OK, a range error can be caught
    cout << s; // OK
    delete q;  // OK
}

```
##### Note

`owner<T*>` represents ownership, `zstring` represents a C-style string.

**Also**: Assume that a `T*` obtained from a smart pointer to `T` (e.g., `unique_ptr<T>`) points to a single element.

**See also**: [Support library](I-23-Guideline support library.md#S-gsl).

##### Enforcement

* (Simple) ((Bounds)) Warn for any arithmetic operation on an expression of pointer type that results in a value of pointer type.

