### <a name="Pro-lifetime-invalid-argument"></a>Lifetime.3: Don't pass a possibly invalid pointer to a function.

##### Reason

The function cannot do anything useful with the pointer.

To resolve the problem, either extend the lifetime of the object the pointer is intended to refer to, or shorten the lifetime of the pointer (move the function call to before the pointed-to object's lifetime ends).

##### Example, bad

```cpp
void f(int*);

void g()
{
    int x = 0;
    int* p = &x;

    if (condition()) {
        int y = 0;
        p = &y;
    } // invalidates p

    f(p);               // BAD, p might be invalid if the branch was taken
}

```
##### Example, good

```cpp
void f()
{
    int x = 0;
    int* p = &x;

    int y = 0;
    if (condition()) {
        p = &y;
    }

    f(p);               // OK, p points to x or y and both are still in scope
}

```
##### Enforcement

* Issue a diagnostic for any function argument that is a pointer that could have been invalidated (could point to an object that was destroyed) along a local code path leading to the dereference. To fix: Extend the lifetime of the pointed-to object, or move the function call to before the pointed-to object's lifetime ends.



