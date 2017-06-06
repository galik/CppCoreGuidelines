### <a name="Rt-raise"></a>T.1: Use templates to raise the level of abstraction of code

##### Reason

Generality. Re-use. Efficiency. Encourages consistent definition of user types.

##### Example, bad

Conceptually, the following requirements are wrong because what we want of `T` is more than just the very low-level concepts of "can be incremented" or "can be added":

```cpp
template<typename T>
    // requires Incrementable<T>
T sum1(vector<T>& v, T s)
{
    for (auto x : v) s += x;
    return s;
}

template<typename T>
    // requires Simple_number<T>
T sum2(vector<T>& v, T s)
{
    for (auto x : v) s = s + x;
    return s;
}

```
Assuming that `Incrementable` does not support `+` and `Simple_number` does not support `+=`, we have overconstrained implementers of `sum1` and `sum2`.
And, in this case, missed an opportunity for a generalization.

##### Example

```cpp
template<typename T>
    // requires Arithmetic<T>
T sum(vector<T>& v, T s)
{
    for (auto x : v) s += x;
    return s;
}

```
Assuming that `Arithmetic` requires both `+` and `+=`, we have constrained the user of `sum` to provide a complete arithmetic type.
That is not a minimal requirement, but it gives the implementer of algorithms much needed freedom and ensures that any `Arithmetic` type
can be used for a wide variety of algorithms.

For additional generality and reusability, we could also use a more general `Container` or `Range` concept instead of committing to only one container, `vector`.

##### Note

If we define a template to require exactly the operations required for a single implementation of a single algorithm
(e.g., requiring just `+=` rather than also `=` and `+`) and only those, we have overconstrained maintainers.
We aim to minimize requirements on template arguments, but the absolutely minimal requirements of an implementation is rarely a meaningful concept.

##### Note

Templates can be used to express essentially everything (they are Turing complete), but the aim of generic programming (as expressed using templates)
is to efficiently generalize operations/algorithms over a set of types with similar semantic properties.

##### Note

The `requires` in the comments are uses of `concepts`.
"Concepts" are defined in an ISO Technical specification: [concepts](http://www.open-std.org/jtc1/sc22/wg21/docs/papers/2015/n4553.pdf).
Currently (July 2016), concepts are supported only in GCC 6.1.
Consequently, we comment out uses of concepts in examples; that is, we use them as formalized comments only.
If you use GCC 6.1, you can uncomment them.

##### Enforcement

* Flag algorithms with "overly simple" requirements, such as direct use of specific operators without a concept.
* Do not flag the definition of the "overly simple" concepts themselves; they may simply be building blocks for more useful concepts.

