### <a name="Rc-matched"></a>C.22: Make default operations consistent

##### Reason

The default operations are conceptually a matched set. Their semantics are interrelated.
Users will be surprised if copy/move construction and copy/move assignment do logically different things. Users will be surprised if constructors and destructors do not provide a consistent view of resource management. Users will be surprised if copy and move don't reflect the way constructors and destructors work.

##### Example, bad

```cpp
class Silly {   // BAD: Inconsistent copy operations
    class Impl {
        // ...
    };
    shared_ptr<Impl> p;
public:
    Silly(const Silly& a) : p{a.p} { *p = *a.p; }   // deep copy
    Silly& operator=(const Silly& a) { p = a.p; }   // shallow copy
    // ...
};

```
These operations disagree about copy semantics. This will lead to confusion and bugs.

##### Enforcement

* (Complex) A copy/move constructor and the corresponding copy/move assignment operator should write to the same member variables at the same level of dereference.
* (Complex) Any member variables written in a copy/move constructor should also be initialized by all other constructors.
* (Complex) If a copy/move constructor performs a deep copy of a member variable, then the destructor should modify the member variable.
* (Complex) If a destructor is modifying a member variable, that member variable should be written in any copy/move constructors or assignment operators.

## <a name="SS-dtor"></a>C.dtor: Destructors

"Does this class need a destructor?" is a surprisingly powerful design question.
For most classes the answer is "no" either because the class holds no resources or because destruction is handled by [the rule of zero](I-07-Constructors%2C%20assignments%2C%20and%20destructors-C.020.md#Rc-zero);
that is, its members can take care of themselves as concerns destruction.
If the answer is "yes", much of the design of the class follows (see [the rule of five](I-07-Constructors%2C%20assignments%2C%20and%20destructors-C.021.md#Rc-five)).

