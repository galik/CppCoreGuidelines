# <a name="S-interfaces"></a>I: Interfaces

An interface is a contract between two parts of a program. Precisely stating what is expected of a supplier of a service and a user of that service is essential.
Having good (easy-to-understand, encouraging efficient use, not error-prone, supporting testing, etc.) interfaces is probably the most important single aspect of code organization.

Interface rule summary:

* [I.1: Make interfaces explicit](I-04-Interfaces-I.001.md#Ri-explicit)
* [I.2: Avoid global variables](I-04-Interfaces-I.002.md#Ri-global)
* [I.3: Avoid singletons](I-04-Interfaces-I.003.md#Ri-singleton)
* [I.4: Make interfaces precisely and strongly typed](I-04-Interfaces-I.004.md#Ri-typed)
* [I.5: State preconditions (if any)](I-04-Interfaces-I.005.md#Ri-pre)
* [I.6: Prefer `Expects()` for expressing preconditions](I-04-Interfaces-I.006.md#Ri-expects)
* [I.7: State postconditions](I-04-Interfaces-I.007.md#Ri-post)
* [I.8: Prefer `Ensures()` for expressing postconditions](I-04-Interfaces-I.008.md#Ri-ensures)
* [I.9: If an interface is a template, document its parameters using concepts](I-04-Interfaces-I.009.md#Ri-concepts)
* [I.10: Use exceptions to signal a failure to perform a required task](I-04-Interfaces-I.010.md#Ri-except)
* [I.11: Never transfer ownership by a raw pointer (`T*`)](I-04-Interfaces-I.011.md#Ri-raw)
* [I.12: Declare a pointer that must not be null as `not_null`](I-04-Interfaces-I.012.md#Ri-nullptr)
* [I.13: Do not pass an array as a single pointer](I-04-Interfaces-I.013.md#Ri-array)
* [I.22: Avoid complex initialization of global objects](I-04-Interfaces-I.022.md#Ri-global-init)
* [I.23: Keep the number of function arguments low](I-04-Interfaces-I.023.md#Ri-nargs)
* [I.24: Avoid adjacent unrelated parameters of the same type](I-04-Interfaces-I.024.md#Ri-unrelated)
* [I.25: Prefer abstract classes as interfaces to class hierarchies](I-04-Interfaces-I.025.md#Ri-abstract)
* [I.26: If you want a cross-compiler ABI, use a C-style subset](I-04-Interfaces-I.026.md#Ri-abi)
* [I.30: Encapsulate rule violations](I-04-Interfaces-I.030.md#Ri-encapsulate)

See also

* [F: Functions](I-05-Functions.md#S-functions)
* [C.concrete: Concrete types](I-06-Classes and Class Hierarchies-C.009.md#SS-concrete)
* [C.hier: Class hierarchies](I-07-Constructors, assignments, and destructors-C.089.md#SS-hier)
* [C.over: Overloading and overloaded operators](I-07-Constructors, assignments, and destructors-C.153.md#SS-overload)
* [C.con: Containers and other resource handles](I-07-Constructors, assignments, and destructors-C.089.md#SS-containers)
* [E: Error handling](I-13-Error handling.md#S-errors)
* [T: Templates and generic programming](I-15-Templates and generic programming.md#S-templates)

