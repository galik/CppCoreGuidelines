# <a name="S-class"></a>C: Classes and Class Hierarchies

A class is a user-defined type, for which a programmer can define the representation, operations, and interfaces.
Class hierarchies are used to organize related classes into hierarchical structures.

Class rule summary:

* [C.1: Organize related data into structures (`struct`s or `class`es)](I-06-Classes%20and%20Class%20Hierarchies-C.001.md#Rc-org)
* [C.2: Use `class` if the class has an invariant; use `struct` if the data members can vary independently](I-06-Classes%20and%20Class%20Hierarchies-C.002.md#Rc-struct)
* [C.3: Represent the distinction between an interface and an implementation using a class](I-06-Classes%20and%20Class%20Hierarchies-C.003.md#Rc-interface)
* [C.4: Make a function a member only if it needs direct access to the representation of a class](I-06-Classes%20and%20Class%20Hierarchies-C.004.md#Rc-member)
* [C.5: Place helper functions in the same namespace as the class they support](I-06-Classes%20and%20Class%20Hierarchies-C.005.md#Rc-helper)
* [C.7: Don't define a class or enum and declare a variable of its type in the same statement](I-06-Classes%20and%20Class%20Hierarchies-C.007.md#Rc-standalone)
* [C.8: Use `class` rather than `struct` if any member is non-public](I-06-Classes%20and%20Class%20Hierarchies-C.008.md#Rc-class)
* [C.9: Minimize exposure of members](I-06-Classes%20and%20Class%20Hierarchies-C.009.md#Rc-private)

Subsections:

* [C.concrete: Concrete types](I-06-Classes%20and%20Class%20Hierarchies-C.009.md#SS-concrete)
* [C.ctor: Constructors, assignments, and destructors](I-07-Constructors%2C%20assignments%2C%20and%20destructors.md#S-ctor)
* [C.con: Containers and other resource handles](I-07-Constructors%2C%20assignments%2C%20and%20destructors-C.089.md#SS-containers)
* [C.lambdas: Function objects and lambdas](I-07-Constructors%2C%20assignments%2C%20and%20destructors-C.089.md#SS-lambdas)
* [C.hier: Class hierarchies (OOP)](I-07-Constructors%2C%20assignments%2C%20and%20destructors-C.089.md#SS-hier)
* [C.over: Overloading and overloaded operators](I-07-Constructors%2C%20assignments%2C%20and%20destructors-C.153.md#SS-overload)
* [C.union: Unions](I-07-Constructors%2C%20assignments%2C%20and%20destructors-C.170.md#SS-union)

