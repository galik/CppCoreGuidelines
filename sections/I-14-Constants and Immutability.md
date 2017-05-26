# <a name="S-const"></a>Con: Constants and Immutability

You can't have a race condition on a constant.
It is easier to reason about a program when many of the objects cannot change their values.
Interfaces that promises "no change" of objects passed as arguments greatly increase readability.

Constant rule summary:

* [Con.1: By default, make objects immutable](I-14-Constants and Immutability-Con.001.md#Rconst-immutable)
* [Con.2: By default, make member functions `const`](I-14-Constants and Immutability-Con.002.md#Rconst-fct)
* [Con.3: By default, pass pointers and references to `const`s](I-14-Constants and Immutability-Con.003.md#Rconst-ref)
* [Con.4: Use `const` to define objects with values that do not change after construction](I-14-Constants and Immutability-Con.004.md#Rconst-const)
* [Con.5: Use `constexpr` for values that can be computed at compile time](I-14-Constants and Immutability-Con.005.md#Rconst-constexpr)

