### <a name="Rt-refine"></a>T.23: Differentiate a refined concept from its more general case by adding new use patterns.

##### Reason

Otherwise they cannot be distinguished automatically by the compiler.

##### Example (using TS concepts)

```cpp
template<typename I>
concept bool Input_iter = requires(I iter) { ++iter; };

template<typename I>
concept bool Fwd_iter = Input_iter<I> && requires(I iter) { iter++; }

```
The compiler can determine refinement based on the sets of required operations (here, suffix `++`).
This decreases the burden on implementers of these types since
they do not need any special declarations to "hook into the concept".
If two concepts have exactly the same requirements, they are logically equivalent (there is no refinement).

##### Enforcement

* Flag a concept that has exactly the same requirements as another already-seen concept (neither is more refined).
To disambiguate them, see [T.24](I-15-Templates%20and%20generic%20programming-T.024.md#Rt-tag).

