### <a name="Rf-return-ref"></a>F.44: Return a `T&` when copy is undesirable and "returning no object" isn't needed

##### Reason

The language guarantees that a `T&` refers to an object, so that testing for `nullptr` isn't necessary.

**See also**: The return of a reference must not imply transfer of ownership:
[discussion of dangling pointer prevention](#???) and [discussion of ownership](#???).

##### Example

```cpp
class Car
{
    array<wheel, 4> w;
    // ...
public:
    wheel& get_wheel(size_t i) { Expects(i < 4); return w[i]; }
    // ...
};

void use()
{
    Car c;
    wheel& w0 = c.get_wheel(0); // w0 has the same lifetime as c
}

```
##### Enforcement

Flag functions where no `return` expression could yield `nullptr`

