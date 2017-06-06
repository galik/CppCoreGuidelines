### <a name="Rh-virtual"></a>C.132: Don't make a function `virtual` without reason

##### Reason

Redundant `virtual` increases run-time and object-code size.
A virtual function can be overridden and is thus open to mistakes in a derived class.
A virtual function ensures code replication in a templated hierarchy.

##### Example, bad

```cpp
template<class T>
class Vector {
public:
    // ...
    virtual int size() const { return sz; }   // bad: what good could a derived class do?
private:
    T* elem;   // the elements
    int sz;    // number of elements
};

```
This kind of "vector" isn't meant to be used as a base class at all.

##### Enforcement

* Flag a class with virtual functions but no derived classes.
* Flag a class where all member functions are virtual and have implementations.

