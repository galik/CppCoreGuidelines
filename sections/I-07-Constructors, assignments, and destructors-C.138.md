### <a name="Rh-using"></a>C.138: Create an overload set for a derived class and its bases with `using`

##### Reason

Without a using declaration, member functions in the derived class hide the entire inherited overload sets.

##### Example, bad

```cpp
#include <iostream>
class B {
public:
    virtual int f(int i) { std::cout << "f(int): "; return i; }
    virtual double f(double d) { std::cout << "f(double): "; return d; }
};
class D: public B {
public:
    int f(int i) override { std::cout << "f(int): "; return i+1; }
};
int main()
{
    D d;
    std::cout << d.f(2) << '\n';   // prints "f(int): 3"
    std::cout << d.f(2.3) << '\n'; // prints "f(int): 3"
}

```
##### Example, good

```cpp
class D: public B {
public:
    int f(int i) override { std::cout << "f(int): "; return i+1; }
    using B::f; // exposes f(double)
};

```
##### Note

This issue affects both virtual and non-virtual member functions

For variadic bases, C++17 introduced a variadic form of the using-declaration,

```cpp
template <class... Ts>
struct Overloader : Ts... {
    using Ts::operator()...; // exposes operator() from every base
};

```
##### Enforcement

Diagnose name hiding

