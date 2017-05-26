# <a name="S-ctor"></a>C.ctor: Constructors, assignments, and destructors

These functions control the lifecycle of objects: creation, copy, move, and destruction.
Define constructors to guarantee and simplify initialization of classes.

These are *default operations*:

* a default constructor: `X()`
* a copy constructor: `X(const X&)`
* a copy assignment: `operator=(const X&)`
* a move constructor: `X(X&&)`
* a move assignment: `operator=(X&&)`
* a destructor: `~X()`

By default, the compiler defines each of these operations if it is used, but the default can be suppressed.

The default operations are a set of related operations that together implement the lifecycle semantics of an object.
By default, C++ treats classes as value-like types, but not all types are value-like.

Set of default operations rules:

* [C.20: If you can avoid defining any default operations, do](I-07-Constructors, assignments, and destructors-C.020.md#Rc-zero)
* [C.21: If you define or `=delete` any default operation, define or `=delete` them all](I-07-Constructors, assignments, and destructors-C.021.md#Rc-five)
* [C.22: Make default operations consistent](I-07-Constructors, assignments, and destructors-C.022.md#Rc-matched)

Destructor rules:

* [C.30: Define a destructor if a class needs an explicit action at object destruction](I-07-Constructors, assignments, and destructors-C.030.md#Rc-dtor)
* [C.31: All resources acquired by a class must be released by the class's destructor](I-07-Constructors, assignments, and destructors-C.031.md#Rc-dtor-release)
* [C.32: If a class has a raw pointer (`T*`) or reference (`T&`), consider whether it might be owning](I-07-Constructors, assignments, and destructors-C.032.md#Rc-dtor-ptr)
* [C.33: If a class has an owning pointer member, define or `=delete` a destructor](I-07-Constructors, assignments, and destructors-C.033.md#Rc-dtor-ptr2)
* [C.34: If a class has an owning reference member, define or `=delete` a destructor](I-07-Constructors, assignments, and destructors-C.034.md#Rc-dtor-ref)
* [C.35: A base class with a virtual function needs a virtual destructor](I-07-Constructors, assignments, and destructors-C.035.md#Rc-dtor-virtual)
* [C.36: A destructor may not fail](I-07-Constructors, assignments, and destructors-C.036.md#Rc-dtor-fail)
* [C.37: Make destructors `noexcept`](I-07-Constructors, assignments, and destructors-C.037.md#Rc-dtor-noexcept)

Constructor rules:

* [C.40: Define a constructor if a class has an invariant](I-07-Constructors, assignments, and destructors-C.040.md#Rc-ctor)
* [C.41: A constructor should create a fully initialized object](I-07-Constructors, assignments, and destructors-C.041.md#Rc-complete)
* [C.42: If a constructor cannot construct a valid object, throw an exception](I-07-Constructors, assignments, and destructors-C.042.md#Rc-throw)
* [C.43: Ensure that a value type class has a default constructor](I-07-Constructors, assignments, and destructors-C.043.md#Rc-default0)
* [C.44: Prefer default constructors to be simple and non-throwing](I-07-Constructors, assignments, and destructors-C.044.md#Rc-default00)
* [C.45: Don't define a default constructor that only initializes data members; use member initializers instead](I-07-Constructors, assignments, and destructors-C.045.md#Rc-default)
* [C.46: By default, declare single-argument constructors `explicit`](I-07-Constructors, assignments, and destructors-C.046.md#Rc-explicit)
* [C.47: Define and initialize member variables in the order of member declaration](I-07-Constructors, assignments, and destructors-C.047.md#Rc-order)
* [C.48: Prefer in-class initializers to member initializers in constructors for constant initializers](I-07-Constructors, assignments, and destructors-C.048.md#Rc-in-class-initializer)
* [C.49: Prefer initialization to assignment in constructors](I-07-Constructors, assignments, and destructors-C.049.md#Rc-initialize)
* [C.50: Use a factory function if you need "virtual behavior" during initialization](I-07-Constructors, assignments, and destructors-C.050.md#Rc-factory)
* [C.51: Use delegating constructors to represent common actions for all constructors of a class](I-07-Constructors, assignments, and destructors-C.051.md#Rc-delegating)
* [C.52: Use inheriting constructors to import constructors into a derived class that does not need further explicit initialization](I-07-Constructors, assignments, and destructors-C.052.md#Rc-inheriting)

Copy and move rules:

* [C.60: Make copy assignment non-`virtual`, take the parameter by `const&`, and return by non-`const&`](I-07-Constructors, assignments, and destructors-C.060.md#Rc-copy-assignment)
* [C.61: A copy operation should copy](I-07-Constructors, assignments, and destructors-C.061.md#Rc-copy-semantic)
* [C.62: Make copy assignment safe for self-assignment](I-07-Constructors, assignments, and destructors-C.062.md#Rc-copy-self)
* [C.63: Make move assignment non-`virtual`, take the parameter by `&&`, and return by non-`const&`](I-07-Constructors, assignments, and destructors-C.063.md#Rc-move-assignment)
* [C.64: A move operation should move and leave its source in a valid state](I-07-Constructors, assignments, and destructors-C.064.md#Rc-move-semantic)
* [C.65: Make move assignment safe for self-assignment](I-07-Constructors, assignments, and destructors-C.065.md#Rc-move-self)
* [C.66: Make move operations `noexcept`](I-07-Constructors, assignments, and destructors-C.066.md#Rc-move-noexcept)
* [C.67: A base class should suppress copying, and provide a virtual `clone` instead if "copying" is desired](I-07-Constructors, assignments, and destructors-C.067.md#Rc-copy-virtual)

Other default operations rules:

* [C.80: Use `=default` if you have to be explicit about using the default semantics](I-07-Constructors, assignments, and destructors-C.080.md#Rc-eqdefault)
* [C.81: Use `=delete` when you want to disable default behavior (without wanting an alternative)](I-07-Constructors, assignments, and destructors-C.081.md#Rc-delete)
* [C.82: Don't call virtual functions in constructors and destructors](I-07-Constructors, assignments, and destructors-C.082.md#Rc-ctor-virtual)
* [C.83: For value-like types, consider providing a `noexcept` swap function](I-07-Constructors, assignments, and destructors-C.083.md#Rc-swap)
* [C.84: A `swap` may not fail](I-07-Constructors, assignments, and destructors-C.084.md#Rc-swap-fail)
* [C.85: Make `swap` `noexcept`](I-07-Constructors, assignments, and destructors-C.085.md#Rc-swap-noexcept)
* [C.86: Make `==` symmetric with respect of operand types and `noexcept`](I-07-Constructors, assignments, and destructors-C.086.md#Rc-eq)
* [C.87: Beware of `==` on base classes](I-07-Constructors, assignments, and destructors-C.087.md#Rc-eq-base)
* [C.89: Make a `hash` `noexcept`](I-07-Constructors, assignments, and destructors-C.089.md#Rc-hash)

## <a name="SS-defop"></a>C.defop: Default Operations

By default, the language supplies the default operations with their default semantics.
However, a programmer can disable or replace these defaults.

