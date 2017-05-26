### <a name="Rc-swap"></a>C.83: For value-like types, consider providing a `noexcept` swap function

##### Reason

A `swap` can be handy for implementing a number of idioms, from smoothly moving objects around to implementing assignment easily to providing a guaranteed commit function that enables strongly error-safe calling code. Consider using swap to implement copy assignment in terms of copy construction. See also [destructors, deallocation, and swap must never fail](I-13-Error handling-E.016.md#Re-never-fail).

##### Example, good

```cpp
class Foo {
    // ...
public:
    void swap(Foo& rhs) noexcept
    {
        m1.swap(rhs.m1);
        std::swap(m2, rhs.m2);
    }
private:
    Bar m1;
    int m2;
};

```
Providing a nonmember `swap` function in the same namespace as your type for callers' convenience.

```cpp
void swap(Foo& a, Foo& b)
{
    a.swap(b);
}

```
##### Enforcement

* (Simple) A class without virtual functions should have a `swap` member function declared.
* (Simple) When a class has a `swap` member function, it should be declared `noexcept`.

