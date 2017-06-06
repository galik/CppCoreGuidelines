### <a name="Rt-using"></a>T.43: Prefer `using` over `typedef` for defining aliases

##### Reason

Improved readability: With `using`, the new name comes first rather than being embedded somewhere in a declaration.
Generality: `using` can be used for template aliases, whereas `typedef`s can't easily be templates.
Uniformity: `using` is syntactically similar to `auto`.

##### Example

```cpp
typedef int (*PFI)(int);   // OK, but convoluted

using PFI2 = int (*)(int);   // OK, preferred

template<typename T>
typedef int (*PFT)(T);      // error

template<typename T>
using PFT2 = int (*)(T);   // OK

```
##### Enforcement

* Flag uses of `typedef`. This will give a lot of "hits" :-(

