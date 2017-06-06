### <a name="Rc-private"></a>C.9: Minimize exposure of members

##### Reason

Encapsulation.
Information hiding.
Minimize the chance of untended access.
This simplifies maintenance.

##### Example

```cpp
template<typename T, typename U>
struct pair {
    T a;
    U b;
    // ...
};

```
Whatever we do in the `//`-part, an arbitrary user of a `pair` can arbitrarily and independently change its `a` and `b`.
In a large code base, we cannot easily find which code does what to the members of `pair`.
This may be exactly what we want, but if we want to enforce a relation among members, we need to make them `private`
and enforce that relation (invariant) through constructors and member functions.
For example:

```cpp
struct Distance {
public:
    // ...
    double meters() const { return magnitude*unit; }
    void set_unit(double u)
    {
            // ... check that u is a factor of 10 ...
            // ... change magnitude appropriately ...
            unit = u;
    }
    // ...
private:
    double magnitude;
    double unit;    // 1 is meters, 1000 is kilometers, 0.0001 is millimeters, etc.
};

```
##### Note

If the set of direct users of a set of variables cannot be easily determined, the type or usage of that set cannot be (easily) changed/improved.
For `public` and `protected` data, that's usually the case.

##### Example

A class can provide two interfaces to its users.
One for derived classes (`protected`) and one for general users (`public`).
For example, a derived class might be allowed to skip a run-time check because it has already guaranteed correctness:

```cpp
class Foo {
public:
    int bar(int x) { check(x); return do_bar(); }
    // ...
protected:
    int do_bar(int x); // do some operation on the data
    // ...
private:
    // ... data ...
};

class Dir : public Foo {
    //...
    int mem(int x, int y)
    {
        /* ... do something ... */
        return do_bar(x + y); // OK: derived class can bypass check
    }
}

void user(Foo& x)
{
    int r1 = x.bar(1);      // OK, will check
    int r2 = x.do_bar(2);   // error: would bypass check
    // ...
}

```
##### Note

[`protected` data is a bad idea](I-07-Constructors%2C%20assignments%2C%20and%20destructors-C.133.md#Rh-protected).

##### Note

Prefer the order `public` members before `protected` members before `private` members [see](I-24-Naming%20and%20layout%20rules-NL.016.md#Rl-order).

##### Enforcement

* [Flag protected data](I-07-Constructors%2C%20assignments%2C%20and%20destructors-C.133.md#Rh-protected).
* Flag mixtures of `public` and private `data`

## <a name="SS-concrete"></a>C.concrete: Concrete types

One ideal for a class is to be a regular type.
That means roughly "behaves like an `int`." A concrete type is the simplest kind of class.
A value of regular type can be copied and the result of a copy is an independent object with the same value as the original.
If a concrete type has both `=` and `==`, `a = b` should result in `a == b` being `true`.
Concrete classes without assignment and equality can be defined, but they are (and should be) rare.
The C++ built-in types are regular, and so are standard-library classes, such as `string`, `vector`, and `map`.
Concrete types are also often referred to as value types to distinguish them from types used as part of a hierarchy.

Concrete type rule summary:

* [C.10: Prefer concrete types over class hierarchies](I-06-Classes%20and%20Class%20Hierarchies-C.010.md#Rc-concrete)
* [C.11: Make concrete types regular](I-06-Classes%20and%20Class%20Hierarchies-C.011.md#Rc-regular)

