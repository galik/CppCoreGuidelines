### <a name="Res-unique"></a>ES.24: Use a `unique_ptr<T>` to hold pointers

##### Reason

Using `std::unique_ptr` is the simplest way to avoid leaks. It is reliable, it
makes the type system do much of the work to validate ownership safety, it
increases readability, and it has zero or near zero runtime cost.

##### Example

```cpp
void use(bool leak)
{
    auto p1 = make_unique<int>(7);   // OK
    int* p2 = new int{7};            // bad: might leak
    // ... no assignment to p2 ...
    if (leak) return;
    // ... no assignment to p2 ...
    vector<int> v(7);
    v.at(7) = 0;                    // exception thrown
    // ...
}

```
If `leak == true` the object pointed to by `p2` is leaked and the object pointed to by `p1` is not.
The same is the case when `at()` throws.

##### Enforcement

Look for raw pointers that are targets of `new`, `malloc()`, or functions that may return such pointers.

