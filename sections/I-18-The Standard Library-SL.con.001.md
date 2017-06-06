### <a name="Rsl-arrays"></a>SL.con.1: Prefer using STL `array` or `vector` instead of a C array

##### Reason

C arrays are less safe, and have no advantages over `array` and `vector`.
For a fixed-length array, use `std::array`, which does not degenerate to a pointer when passed to a function and does know its size.
Also, like a built-in array, a stack-allocated `std::array` keeps its elements on the stack.
For a variable-length array, use `std::vector`, which additionally can change its size and handles memory allocation.

##### Example

```cpp
int v[SIZE];                        // BAD

std::array<int, SIZE> w;             // ok

```
##### Example

```cpp
int* v = new int[initial_size];     // BAD, owning raw pointer
delete[] v;                         // BAD, manual delete

std::vector<int> w(initial_size);   // ok

```
##### Note

Use `gsl::span` for non-owning references into a container.

##### Enforcement

* Flag declaration of a C array inside a function or class that also declares an STL container (to avoid excessive noisy warnings on legacy non-STL code). To fix: At least change the C array to a `std::array`.

