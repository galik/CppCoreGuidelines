### <a name="Rcpl-subset"></a>CPL.2: If you must use C, use the common subset of C and C++, and compile the C code as C++

##### Reason

That subset can be compiled with both C and C++ compilers, and when compiled as C++ is better type checked than "pure C."

##### Example

```cpp
int* p1 = malloc(10 * sizeof(int));                      // not C++
int* p2 = static_cast<int*>(malloc(10 * sizeof(int)));   // not C, C-style C++
int* p3 = new int[10];                                   // not C
int* p4 = (int*) malloc(10 * sizeof(int));               // both C and C++

```
##### Enforcement

* Flag if using a build mode that compiles code as C.

  * The C++ compiler will enforce that the code is valid C++ unless you use C extension options.

