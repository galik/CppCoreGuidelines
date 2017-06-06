### <a name="Rr-owner"></a>R.20: Use `unique_ptr` or `shared_ptr` to represent ownership

##### Reason

They can prevent resource leaks.

##### Example

Consider:

```cpp
void f()
{
    X x;
    X* p1 { new X };              // see also ???
    unique_ptr<T> p2 { new X };   // unique ownership; see also ???
    shared_ptr<T> p3 { new X };   // shared ownership; see also ???
}

```
This will leak the object used to initialize `p1` (only).

##### Enforcement

(Simple) Warn if the return value of `new` or a function call with return value of pointer type is assigned to a raw pointer.

