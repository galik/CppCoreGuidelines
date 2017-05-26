### <a name="Res-lib"></a>ES.1: Prefer the standard library to other libraries and to "handcrafted code"

##### Reason

Code using a library can be much easier to write than code working directly with language features, much shorter, tend to be of a higher level of abstraction, and the library code is presumably already tested.
The ISO C++ standard library is among the most widely known and best tested libraries.
It is available as part of all C++ Implementations.

##### Example

```cpp
auto sum = accumulate(begin(a), end(a), 0.0);   // good

```
a range version of `accumulate` would be even better:

```cpp
auto sum = accumulate(v, 0.0); // better

```
but don't hand-code a well-known algorithm:

```cpp
int max = v.size();   // bad: verbose, purpose unstated
double sum = 0.0;
for (int i = 0; i < max; ++i)
    sum = sum + v[i];

```
##### Exception

Large parts of the standard library rely on dynamic allocation (free store). These parts, notably the containers but not the algorithms, are unsuitable for some hard-real time and embedded applications. In such cases, consider providing/using similar facilities, e.g.,  a standard-library-style container implemented using a pool allocator.

##### Enforcement

Not easy. ??? Look for messy loops, nested loops, long functions, absence of function calls, lack of use of non-built-in types. Cyclomatic complexity?

