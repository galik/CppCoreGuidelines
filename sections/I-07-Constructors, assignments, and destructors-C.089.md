### <a name="Rc-hash"></a>C.89: Make a `hash` `noexcept`

##### Reason

Users of hashed containers use hash indirectly and don't expect simple access to throw.
It's a standard-library requirement.

##### Example, bad

```cpp
template<>
struct hash<My_type> {  // thoroughly bad hash specialization
    using result_type = size_t;
    using argument_type = My_type;

    size_t operator() (const My_type & x) const
    {
        size_t xs = x.s.size();
        if (xs < 4) throw Bad_My_type{};    // "Nobody expects the Spanish inquisition!"
        return hash<size_t>()(x.s.size()) ^ trim(x.s);
    }
};

int main()
{
    unordered_map<My_type, int> m;
    My_type mt{ "asdfg" };
    m[mt] = 7;
    cout << m[My_type{ "asdfg" }] << '\n';
}

```
If you have to define a `hash` specialization, try simply to let it combine standard-library `hash` specializations with `^` (xor).
That tends to work better than "cleverness" for non-specialists.

##### Enforcement

* Flag throwing `hash`es.

## <a name="SS-containers"></a>C.con: Containers and other resource handles

A container is an object holding a sequence of objects of some type; `std::vector` is the archetypical container.
A resource handle is a class that owns a resource; `std::vector` is the typical resource handle; its resource is its sequence of elements.

Summary of container rules:

* [C.100: Follow the STL when defining a container](#Rcon-stl)
* [C.101: Give a container value semantics](#Rcon-val)
* [C.102: Give a container move operations](#Rcon-move)
* [C.103: Give a container an initializer list constructor](#Rcon-init)
* [C.104: Give a container a default constructor that sets it to empty](#Rcon-empty)
* [C.105: Give a constructor and `Extent` constructor](#Rcon-val)
* ???
* [C.109: If a resource handle has pointer semantics, provide `*` and `->`](#rcon-ptr)

**See also**: [Resources](I-09-Resource%20management.md#S-resource)

## <a name="SS-lambdas"></a>C.lambdas: Function objects and lambdas

A function object is an object supplying an overloaded `()` so that you can call it.
A lambda expression (colloquially often shortened to "a lambda") is a notation for generating a function object.
Function objects should be cheap to copy (and therefore [passed by value](I-05-Functions-F.016.md#Rf-in)).

Summary:

* [F.50: Use a lambda when a function won't do (to capture local variables, or to write a local function)](I-05-Functions-F.050.md#Rf-capture-vs-overload)
* [F.52: Prefer capturing by reference in lambdas that will be used locally, including passed to algorithms](I-05-Functions-F.052.md#Rf-reference-capture)
* [F.53: Avoid capturing by reference in lambdas that will be used nonlocally, including returned, stored on the heap, or passed to another thread](I-05-Functions-F.053.md#Rf-value-capture)
* [ES.28: Use lambdas for complex initialization, especially of `const` variables](I-10-Expressions%20and%20Statements-ES.028.md#Res-lambda-init)

## <a name="SS-hier"></a>C.hier: Class hierarchies (OOP)

A class hierarchy is constructed to represent a set of hierarchically organized concepts (only).
Typically base classes act as interfaces.
There are two major uses for hierarchies, often named implementation inheritance and interface inheritance.

Class hierarchy rule summary:

* [C.120: Use class hierarchies to represent concepts with inherent hierarchical structure (only)](I-07-Constructors%2C%20assignments%2C%20and%20destructors-C.120.md#Rh-domain)
* [C.121: If a base class is used as an interface, make it a pure abstract class](I-07-Constructors%2C%20assignments%2C%20and%20destructors-C.121.md#Rh-abstract)
* [C.122: Use abstract classes as interfaces when complete separation of interface and implementation is needed](I-07-Constructors%2C%20assignments%2C%20and%20destructors-C.122.md#Rh-separation)

Designing rules for classes in a hierarchy summary:

* [C.126: An abstract class typically doesn't need a constructor](I-07-Constructors%2C%20assignments%2C%20and%20destructors-C.126.md#Rh-abstract-ctor)
* [C.127: A class with a virtual function should have a virtual or protected destructor](I-07-Constructors%2C%20assignments%2C%20and%20destructors-C.127.md#Rh-dtor)
* [C.128: Virtual functions should specify exactly one of `virtual`, `override`, or `final`](I-07-Constructors%2C%20assignments%2C%20and%20destructors-C.128.md#Rh-override)
* [C.129: When designing a class hierarchy, distinguish between implementation inheritance and interface inheritance](I-07-Constructors%2C%20assignments%2C%20and%20destructors-C.129.md#Rh-kind)
* [C.130: Redefine or prohibit copying for a base class; prefer a virtual `clone` function instead](I-07-Constructors%2C%20assignments%2C%20and%20destructors-C.130.md#Rh-copy)
* [C.131: Avoid trivial getters and setters](I-07-Constructors%2C%20assignments%2C%20and%20destructors-C.131.md#Rh-get)
* [C.132: Don't make a function `virtual` without reason](I-07-Constructors%2C%20assignments%2C%20and%20destructors-C.132.md#Rh-virtual)
* [C.133: Avoid `protected` data](I-07-Constructors%2C%20assignments%2C%20and%20destructors-C.133.md#Rh-protected)
* [C.134: Ensure all non-`const` data members have the same access level](I-07-Constructors%2C%20assignments%2C%20and%20destructors-C.134.md#Rh-public)
* [C.135: Use multiple inheritance to represent multiple distinct interfaces](I-07-Constructors%2C%20assignments%2C%20and%20destructors-C.135.md#Rh-mi-interface)
* [C.136: Use multiple inheritance to represent the union of implementation attributes](I-07-Constructors%2C%20assignments%2C%20and%20destructors-C.136.md#Rh-mi-implementation)
* [C.137: Use `virtual` bases to avoid overly general base classes](I-07-Constructors%2C%20assignments%2C%20and%20destructors-C.137.md#Rh-vbase)
* [C.138: Create an overload set for a derived class and its bases with `using`](I-07-Constructors%2C%20assignments%2C%20and%20destructors-C.138.md#Rh-using)
* [C.139: Use `final` sparingly](I-07-Constructors%2C%20assignments%2C%20and%20destructors-C.139.md#Rh-final)
* [C.140: Do not provide different default arguments for a virtual function and an overrider](I-07-Constructors%2C%20assignments%2C%20and%20destructors-C.139.md#Rh-virtual-default-arg)

Accessing objects in a hierarchy rule summary:

* [C.145: Access polymorphic objects through pointers and references](I-07-Constructors%2C%20assignments%2C%20and%20destructors-C.145.md#Rh-poly)
* [C.146: Use `dynamic_cast` where class hierarchy navigation is unavoidable](I-07-Constructors%2C%20assignments%2C%20and%20destructors-C.146.md#Rh-dynamic_cast)
* [C.147: Use `dynamic_cast` to a reference type when failure to find the required class is considered an error](I-07-Constructors%2C%20assignments%2C%20and%20destructors-C.147.md#Rh-ref-cast)
* [C.148: Use `dynamic_cast` to a pointer type when failure to find the required class is considered a valid alternative](I-07-Constructors%2C%20assignments%2C%20and%20destructors-C.148.md#Rh-ptr-cast)
* [C.149: Use `unique_ptr` or `shared_ptr` to avoid forgetting to `delete` objects created using `new`](I-07-Constructors%2C%20assignments%2C%20and%20destructors-C.149.md#Rh-smart)
* [C.150: Use `make_unique()` to construct objects owned by `unique_ptr`s](I-07-Constructors%2C%20assignments%2C%20and%20destructors-C.150.md#Rh-make_unique)
* [C.151: Use `make_shared()` to construct objects owned by `shared_ptr`s](I-07-Constructors%2C%20assignments%2C%20and%20destructors-C.151.md#Rh-make_shared)
* [C.152: Never assign a pointer to an array of derived class objects to a pointer to its base](I-07-Constructors%2C%20assignments%2C%20and%20destructors-C.152.md#Rh-array)
* [C.153: Prefer virtual function to casting](I-07-Constructors%2C%20assignments%2C%20and%20destructors-C.153.md#Rh-use-virtual)

