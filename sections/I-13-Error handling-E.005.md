### <a name="Re-invariant"></a>E.5: Let a constructor establish an invariant, and throw if it cannot

##### Reason

Leaving an object without its invariant established is asking for trouble.
Not all member functions can be called.

##### Example

```cpp
class Vector {  // very simplified vector of doubles
    // if elem != nullptr then elem points to sz doubles
public:
    Vector() : elem{nullptr}, sz{0}{}
    Vector(int s) : elem{new double}, sz{s} { /* initialize elements */ }
    ~Vector() { delete elem; }
    double& operator[](int s) { return elem[s]; }
    // ...
private:
    owner<double*> elem;
    int sz;
};

```
The class invariant - here stated as a comment - is established by the constructors.
`new` throws if it cannot allocate the required memory.
The operators, notably the subscript operator, relies on the invariant.

**See also**: [If a constructor cannot construct a valid object, throw an exception](I-07-Constructors, assignments, and destructors-C.042.md#Rc-throw)

##### Enforcement

Flag classes with `private` state without a constructor (public, protected, or private).

