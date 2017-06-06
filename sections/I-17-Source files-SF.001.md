### <a name="Rs-file-suffix"></a>SF.1: Use a `.cpp` suffix for code files and `.h` for interface files if your project doesn't already follow another convention

##### Reason

It's a longstanding convention.
But consistency is more important, so if your project uses something else, follow that.

##### Note

This convention reflects a common use pattern:
Headers are more often shared with C to compile as both C++ and C, which typically uses `.h`,
and it's easier to name all headers `.h` instead of having different extensions for just those headers that are intended to be shared with C.
On the other hand, implementation files are rarely shared with C and so should typically be distinguished from `.c` files,
so it's normally best to name all C++ implementation files something else (such as `.cpp`).

The specific names `.h` and `.cpp` are not required (just recommended as a default) and other names are in widespread use.
Examples are `.hh`, `.C`, and `.cxx`. Use such names equivalently.
In this document, we refer to `.h` and `.cpp` as a shorthand for header and implementation files,
even though the actual extension may be different.

Your IDE (if you use one) may have strong opinions about suffices.

##### Example

```cpp
// foo.h:
extern int a;   // a declaration
extern void foo();

// foo.cpp:
int a;   // a definition
void foo() { ++a; }

```
`foo.h` provides the interface to `foo.cpp`. Global variables are best avoided.

##### Example, bad

```cpp
// foo.h:
int a;   // a definition
void foo() { ++a; }

```
`#include <foo.h>` twice in a program and you get a linker error for two one-definition-rule violations.

##### Enforcement

* Flag non-conventional file names.
* Check that `.h` and `.cpp` (and equivalents) follow the rules below.

