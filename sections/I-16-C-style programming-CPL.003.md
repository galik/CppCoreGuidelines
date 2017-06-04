### <a name="Rcpl-interface"></a>CPL.3: If you must use C for interfaces, use C++ in the calling code using such interfaces

##### Reason

C++ is more expressive than C and offers better support for many types of programming.

##### Example

For example, to use a 3rd party C library or C systems interface, define the low-level interface in the common subset of C and C++ for better type checking.
Whenever possible encapsulate the low-level interface in an interface that follows the C++ guidelines (for better abstraction, memory safety, and resource safety) and use that C++ interface in C++ code.

##### Example

You can call C from C++:

```cpp
// in C:
double sqrt(double);

// in C++:
extern "C" double sqrt(double);

sqrt(2);

```
##### Example

You can call C++ from C:

```cpp
// in C:
X call_f(struct Y*, int);

// in C++:
extern "C" X call_f(Y* p, int i)
{
    return p->f(i);   // possibly a virtual function call
}

```
##### Enforcement

None needed

