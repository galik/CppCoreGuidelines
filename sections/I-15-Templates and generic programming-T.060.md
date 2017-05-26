### <a name="Rt-depend"></a>T.60: Minimize a template's context dependencies

##### Reason

Eases understanding.
Minimizes errors from unexpected dependencies.
Eases tool creation.

##### Example

```cpp
template<typename C>
void sort(C& c)
{
    std::sort(begin(c), end(c)); // necessary and useful dependency
}

template<typename Iter>
Iter algo(Iter first, Iter last) {
    for (; first != last; ++first) {
        auto x = sqrt(*first); // potentially surprising dependency: which sqrt()?
        helper(first, x);      // potentially surprising dependency:
                               // helper is chosen based on first and x
        TT var = 7;            // potentially surprising dependency: which TT?
    }
}

```
##### Note

Templates typically appear in header files so their context dependencies are more vulnerable to `#include` order dependencies than functions in `.cpp` files.

##### Note

Having a template operate only on its arguments would be one way of reducing the number of dependencies to a minimum, but that would generally be unmanageable.
For example, an algorithm usually uses other algorithms and invoke operations that does not exclusively operate on arguments.
And don't get us started on macros!
See also [T.69](I-15-Templates and generic programming-T.069.md#Rt-customization)

##### Enforcement

??? Tricky

