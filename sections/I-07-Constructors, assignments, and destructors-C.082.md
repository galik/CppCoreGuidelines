### <a name="Rc-ctor-virtual"></a>C.82: Don't call virtual functions in constructors and destructors

##### Reason

The function called will be that of the object constructed so far, rather than a possibly overriding function in a derived class.
This can be most confusing.
Worse, a direct or indirect call to an unimplemented pure virtual function from a constructor or destructor results in undefined behavior.

##### Example, bad

```cpp
class Base {
public:
    virtual void f() = 0;   // not implemented
    virtual void g();       // implemented with Base version
    virtual void h();       // implemented with Base version
};

class Derived : public Base {
public:
    void g() override;   // provide Derived implementation
    void h() final;      // provide Derived implementation

    Derived()
    {
        // BAD: attempt to call an unimplemented virtual function
        f();

        // BAD: will call Derived::g, not dispatch further virtually
        g();

        // GOOD: explicitly state intent to call only the visible version
        Derived::g();

        // ok, no qualification needed, h is final
        h();
    }
};

```
Note that calling a specific explicitly qualified function is not a virtual call even if the function is `virtual`.

**See also** [factory functions](I-07-Constructors, assignments, and destructors-C.050.md#Rc-factory) for how to achieve the effect of a call to a derived class function without risking undefined behavior.

##### Note

There is nothing inherently wrong with calling virtual functions from constructors and destructors.
The semantics of such calls is type safe.
However, experience shows that such calls are rarely needed, easily confuse maintainers, and become a source of errors when used by novices.

##### Enforcement

* Flag calls of virtual functions from constructors and destructors.

