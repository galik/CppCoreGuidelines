### <a name="Rs-consistency"></a>SF.5: A `.cpp` file must include the `.h` file(s) that defines its interface

##### Reason

This enables the compiler to do an early consistency check.

##### Example, bad

```cpp
// foo.h:
void foo(int);
int bar(long);
int foobar(int);

// foo.cpp:
void foo(int) { /* ... */ }
int bar(double) { /* ... */ }
double foobar(int);

```
The errors will not be caught until link time for a program calling `bar` or `foobar`.

##### Example

```cpp
// foo.h:
void foo(int);
int bar(long);
int foobar(int);

// foo.cpp:
#include <foo.h>

void foo(int) { /* ... */ }
int bar(double) { /* ... */ }
double foobar(int);   // error: wrong return type

```
The return-type error for `foobar` is now caught immediately when `foo.cpp` is compiled.
The argument-type error for `bar` cannot be caught until link time because of the possibility of overloading, but systematic use of `.h` files increases the likelihood that it is caught earlier by the programmer.

##### Enforcement

???

