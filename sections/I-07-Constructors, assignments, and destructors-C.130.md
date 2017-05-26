### <a name="Rh-copy"></a>C.130: Redefine or prohibit copying for a base class; prefer a virtual `clone` function instead

##### Reason

Copying a base is usually slicing. If you really need copy semantics, copy deeply: Provide a virtual `clone` function that will copy the actual most-derived type and return an owning pointer to the new object, and then in derived classes return the derived type (use a covariant return type).

##### Example

```cpp
class Base {
public:
    virtual owner<Base*> clone() = 0;
    virtual ~Base() = 0;

    Base(const Base&) = delete;
    Base& operator=(const Base&) = delete;
};

class Derived : public Base {
public:
    owner<Derived*> clone() override;
    virtual ~Derived() override;
};

```
Note that because of language rules, the covariant return type cannot be a smart pointer. See also [C.67](I-07-Constructors, assignments, and destructors-C.067.md#Rc-copy-virtual).

##### Enforcement

* Flag a class with a virtual function and a non-user-defined copy operation.
* Flag an assignment of base class objects (objects of a class from which another has been derived).

