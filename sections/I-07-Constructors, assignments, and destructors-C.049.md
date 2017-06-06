### <a name="Rc-initialize"></a>C.49: Prefer initialization to assignment in constructors

##### Reason

An initialization explicitly states that initialization, rather than assignment, is done and can be more elegant and efficient. Prevents "use before set" errors.

##### Example, good

```cpp
class A {   // Good
    string s1;
public:
    A() : s1{"Hello, "} { }    // GOOD: directly construct
    // ...
};

```
##### Example, bad

```cpp
class B {   // BAD
    string s1;
public:
    B() { s1 = "Hello, "; }   // BAD: default constructor followed by assignment
    // ...
};

class C {   // UGLY, aka very bad
    int* p;
public:
    C() { cout << *p; p = new int{10}; }   // accidental use before initialized
    // ...
};

```
