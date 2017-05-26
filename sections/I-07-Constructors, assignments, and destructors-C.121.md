### <a name="Rh-abstract"></a>C.121: If a base class is used as an interface, make it a pure abstract class

##### Reason

A class is more stable (less brittle) if it does not contain data.
Interfaces should normally be composed entirely of public pure virtual functions and a default/empty virtual destructor.

##### Example

```cpp
class My_interface {
public:
    // ...only pure virtual functions here ...
    virtual ~My_interface() {}   // or =default
};

```
##### Example, bad

```cpp
class Goof {
public:
    // ...only pure virtual functions here ...
    // no virtual destructor
};

class Derived : public Goof {
    string s;
    // ...
};

void use()
{
    unique_ptr<Goof> p {new Derived{"here we go"}};
    f(p.get()); // use Derived through the Goof interface
    g(p.get()); // use Derived through the Goof interface
} // leak

```
The `Derived` is `delete`d through its `Goof` interface, so its `string` is leaked.
Give `Goof` a virtual destructor and all is well.


##### Enforcement

* Warn on any class that contains data members and also has an overridable (non-`final`) virtual function.

