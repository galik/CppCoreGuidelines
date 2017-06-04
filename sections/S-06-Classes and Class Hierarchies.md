# <a name="S-class"></a>C: Classes and Class Hierarchies

A class is a user-defined type, for which a programmer can define the representation, operations, and interfaces.
Class hierarchies are used to organize related classes into hierarchical structures.

Class rule summary:

* [C.1: Organize related data into structures (`struct`s or `class`es)](S-06-Classes%20and%20Class%20Hierarchies.md#Rc-org)
* [C.2: Use `class` if the class has an invariant; use `struct` if the data members can vary independently](S-06-Classes%20and%20Class%20Hierarchies.md#Rc-struct)
* [C.3: Represent the distinction between an interface and an implementation using a class](S-06-Classes%20and%20Class%20Hierarchies.md#Rc-interface)
* [C.4: Make a function a member only if it needs direct access to the representation of a class](S-06-Classes%20and%20Class%20Hierarchies.md#Rc-member)
* [C.5: Place helper functions in the same namespace as the class they support](S-06-Classes%20and%20Class%20Hierarchies.md#Rc-helper)
* [C.7: Don't define a class or enum and declare a variable of its type in the same statement](S-06-Classes%20and%20Class%20Hierarchies.md#Rc-standalone)
* [C.8: Use `class` rather than `struct` if any member is non-public](S-06-Classes%20and%20Class%20Hierarchies.md#Rc-class)
* [C.9: Minimize exposure of members](S-06-Classes%20and%20Class%20Hierarchies.md#Rc-private)

Subsections:

* [C.concrete: Concrete types](S-06-Classes%20and%20Class%20Hierarchies.md#SS-concrete)
* [C.ctor: Constructors, assignments, and destructors](S-07-Constructors%2C%20assignments%2C%20and%20destructors.md#S-ctor)
* [C.con: Containers and other resource handles](S-07-Constructors%2C%20assignments%2C%20and%20destructors.md#SS-containers)
* [C.lambdas: Function objects and lambdas](S-07-Constructors%2C%20assignments%2C%20and%20destructors.md#SS-lambdas)
* [C.hier: Class hierarchies (OOP)](S-07-Constructors%2C%20assignments%2C%20and%20destructors.md#SS-hier)
* [C.over: Overloading and overloaded operators](S-07-Constructors%2C%20assignments%2C%20and%20destructors.md#SS-overload)
* [C.union: Unions](S-07-Constructors%2C%20assignments%2C%20and%20destructors.md#SS-union)

### <a name="Rc-org"></a>C.1: Organize related data into structures (`struct`s or `class`es)

##### Reason

Ease of comprehension.
If data is related (for fundamental reasons), that fact should be reflected in code.

##### Example

```cpp
void draw(int x, int y, int x2, int y2);  // BAD: unnecessary implicit relationships
void draw(Point from, Point to);          // better

```
##### Note

A simple class without virtual functions implies no space or time overhead.

##### Note

From a language perspective `class` and `struct` differ only in the default visibility of their members.

##### Enforcement

Probably impossible. Maybe a heuristic looking for data items used together is possible.

### <a name="Rc-struct"></a>C.2: Use `class` if the class has an invariant; use `struct` if the data members can vary independently

##### Reason

Readability.
Ease of comprehension.
The use of `class` alerts the programmer to the need for an invariant.
This is a useful convention.

##### Note

An invariant is a logical condition for the members of an object that a constructor must establish for the public member functions to assume.
After the invariant is established (typically by a constructor) every member function can be called for the object.
An invariant can be stated informally (e.g., in a comment) or more formally using `Expects`.

If all data members can vary independently of each other, no invariant is possible.

##### Example

```cpp
struct Pair {  // the members can vary independently
    string name;
    int volume;
};

```
but:

```cpp
class Date {
public:
    // validate that {yy, mm, dd} is a valid date and initialize
    Date(int yy, Month mm, char dd);
    // ...
private:
    int y;
    Month m;
    char d;    // day
};

```
##### Note

If a class has any `private` data, a user cannot completely initialize an object without the use of a constructor.
Hence, the class definer will provide a constructor and must specify its meaning.
This effectively means the definer need to define an invariant.

* See also [define a class with private data as `class`](S-06-Classes%20and%20Class%20Hierarchies.md#Rc-class).
* See also [Prefer to place the interface first in a class](S-24-Naming%20and%20layout%20rules.md#Rl-order).
* See also [minimize exposure of members](S-06-Classes%20and%20Class%20Hierarchies.md#Rc-private).
* See also [Avoid `protected` data](S-07-Constructors%2C%20assignments%2C%20and%20destructors.md#Rh-protected).

##### Enforcement

Look for `struct`s with all data private and `class`es with public members.

### <a name="Rc-interface"></a>C.3: Represent the distinction between an interface and an implementation using a class

##### Reason

An explicit distinction between interface and implementation improves readability and simplifies maintenance.

##### Example

```cpp
class Date {
    // ... some representation ...
public:
    Date();
    // validate that {yy, mm, dd} is a valid date and initialize
    Date(int yy, Month mm, char dd);

    int day() const;
    Month month() const;
    // ...
};

```
For example, we can now change the representation of a `Date` without affecting its users (recompilation is likely, though).

##### Note

Using a class in this way to represent the distinction between interface and implementation is of course not the only way.
For example, we can use a set of declarations of freestanding functions in a namespace, an abstract base class, or a template function with concepts to represent an interface.
The most important issue is to explicitly distinguish between an interface and its implementation "details."
Ideally, and typically, an interface is far more stable than its implementation(s).

##### Enforcement

???

### <a name="Rc-member"></a>C.4: Make a function a member only if it needs direct access to the representation of a class

##### Reason

Less coupling than with member functions, fewer functions that can cause trouble by modifying object state, reduces the number of functions that needs to be modified after a change in representation.

##### Example

```cpp
class Date {
    // ... relatively small interface ...
};

// helper functions:
Date next_weekday(Date);
bool operator==(Date, Date);

```
The "helper functions" have no need for direct access to the representation of a `Date`.

##### Note

This rule becomes even better if C++ gets ["uniform function call"](http://www.open-std.org/jtc1/sc22/wg21/docs/papers/2016/p0251r0.pdf).

##### Exception

The language requires `virtual` functions to be members, and not all `virtual` functions directly access data.
In particular, members of an abstract class rarely do.

Note [multi-methods](https://parasol.tamu.edu/~yuriys/papers/OMM10.pdf).

##### Exception

The language requires operators `=`, `()`, `[]`, and `->` to be members.

##### Exception

An overload set may have some members that do not directly access `private` data:

```cpp
class Foobar {
    void foo(int x)    { /* manipulate private data */ }
    void foo(double x) { foo(std::round(x)); }
    // ...
private:
    // ...
};

```
Similarly, a set of functions may be designed to be used in a chain:

```cpp
x.scale(0.5).rotate(45).set_color(Color::red);

```
Typically, some but not all of such functions directly access `private` data.

##### Enforcement

* Look for non-`virtual` member functions that do not touch data members directly.
The snag is that many member functions that do not need to touch data members directly do.
* Ignore `virtual` functions.
* Ignore functions that are part of an overload set out of which at least one function accesses `private` members.
* Ignore functions returning `this`.

### <a name="Rc-helper"></a>C.5: Place helper functions in the same namespace as the class they support

##### Reason

A helper function is a function (usually supplied by the writer of a class) that does not need direct access to the representation of the class, yet is seen as part of the useful interface to the class.
Placing them in the same namespace as the class makes their relationship to the class obvious and allows them to be found by argument dependent lookup.

##### Example

```cpp
namespace Chrono { // here we keep time-related services

    class Time { /* ... */ };
    class Date { /* ... */ };

    // helper functions:
    bool operator==(Date, Date);
    Date next_weekday(Date);
    // ...
}

```
##### Note

This is especially important for [overloaded operators](S-07-Constructors%2C%20assignments%2C%20and%20destructors.md#Ro-namespace).

##### Enforcement

* Flag global functions taking argument types from a single namespace.

### <a name="Rc-standalone"></a>C.7: Don't define a class or enum and declare a variable of its type in the same statement

##### Reason

Mixing a type definition and the definition of another entity in the same declaration is confusing and unnecessary.

##### Example; bad

```cpp
struct Data { /*...*/ } data{ /*...*/ };

```
##### Example; good

```cpp
struct Data { /*...*/ };
Data data{ /*...*/ };

```
##### Enforcement

* Flag if the `}` of a class or enumeration definition is not followed by a `;`. The `;` is missing.

### <a name="Rc-class"></a>C.8: Use `class` rather than `struct` if any member is non-public

##### Reason

Readability.
To make it clear that something is being hidden/abstracted.
This is a useful convention.

##### Example, bad

```cpp
struct Date {
    int d, m;

    Date(int i, Month m);
    // ... lots of functions ...
private:
    int y;  // year
};

```
There is nothing wrong with this code as far as the C++ language rules are concerned,
but nearly everything is wrong from a design perspective.
The private data is hidden far from the public data.
The data is split in different parts of the class declaration.
Different parts of the data have different access.
All of this decreases readability and complicates maintenance.

##### Note

Prefer to place the interface first in a class [see](S-24-Naming%20and%20layout%20rules.md#Rl-order).

##### Enforcement

Flag classes declared with `struct` if there is a `private` or `public` member.

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

[`protected` data is a bad idea](S-07-Constructors%2C%20assignments%2C%20and%20destructors.md#Rh-protected).

##### Note

Prefer the order `public` members before `protected` members before `private` members [see](S-24-Naming%20and%20layout%20rules.md#Rl-order).

##### Enforcement

* [Flag protected data](S-07-Constructors%2C%20assignments%2C%20and%20destructors.md#Rh-protected).
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

* [C.10: Prefer concrete types over class hierarchies](S-06-Classes%20and%20Class%20Hierarchies.md#Rc-concrete)
* [C.11: Make concrete types regular](S-06-Classes%20and%20Class%20Hierarchies.md#Rc-regular)

### <a name="Rc-concrete"></a>C.10: Prefer concrete types over class hierarchies

##### Reason

A concrete type is fundamentally simpler than a hierarchy:
easier to design, easier to implement, easier to use, easier to reason about, smaller, and faster.
You need a reason (use cases) for using a hierarchy.

##### Example

```cpp
class Point1 {
    int x, y;
    // ... operations ...
    // ... no virtual functions ...
};

class Point2 {
    int x, y;
    // ... operations, some virtual ...
    virtual ~Point2();
};

void use()
{
    Point1 p11 {1, 2};   // make an object on the stack
    Point1 p12 {p11};    // a copy

    auto p21 = make_unique<Point2>(1, 2);   // make an object on the free store
    auto p22 = p21.clone();                 // make a copy
    // ...
}

```
If a class can be part of a hierarchy, we (in real code if not necessarily in small examples) must manipulate its objects through pointers or references.
That implies more memory overhead, more allocations and deallocations, and more run-time overhead to perform the resulting indirections.

##### Note

Concrete types can be stack allocated and be members of other classes.

##### Note

The use of indirection is fundamental for run-time polymorphic interfaces.
The allocation/deallocation overhead is not (that's just the most common case).
We can use a base class as the interface of a scoped object of a derived class.
This is done where dynamic allocation is prohibited (e.g. hard real-time) and to provide a stable interface to some kinds of plug-ins.

##### Enforcement

???

### <a name="Rc-regular"></a>C.11: Make concrete types regular

##### Reason

Regular types are easier to understand and reason about than types that are not regular (irregularities requires extra effort to understand and use).

##### Example

```cpp
struct Bundle {
    string name;
    vector<Record> vr;
};

bool operator==(const Bundle& a, const Bundle& b)
{
    return a.name == b.name && a.vr == b.vr;
}

Bundle b1 { "my bundle", {r1, r2, r3}};
Bundle b2 = b1;
if (!(b1 == b2)) error("impossible!");
b2.name = "the other bundle";
if (b1 == b2) error("No!");

```
In particular, if a concrete type has an assignment also give it an equals operator so that `a = b` implies `a == b`.

##### Enforcement

???

#