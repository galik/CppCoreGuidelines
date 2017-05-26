### <a name="Pro-lifetime-invalid-deref"></a>Lifetime.1: Don't dereference a possibly invalid pointer.

##### Reason

It is undefined behavior.

To resolve the problem, either extend the lifetime of the object the pointer is intended to refer to, or shorten the lifetime of the pointer (move the dereference to before the pointed-to object's lifetime ends).

##### Example, bad

```cpp
void f()
{
    int x = 0;
    int* p = &x;

    if (condition()) {
        int y = 0;
        p = &y;
    } // invalidates p

    *p = 42;            // BAD, p might be invalid if the branch was taken
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

    *p = 42;            // OK, p points to x or y and both are still in scope
}

```
##### Enforcement

* Issue a diagnostic for any dereference of a pointer that could have been invalidated (could point to an object that was destroyed) along a local code path leading to the dereference. To fix: Extend the lifetime of the pointed-to object, or move the dereference to before the pointed-to object's lifetime ends.



