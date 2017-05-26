### <a name="Rt-shorthand"></a>T.13: Prefer the shorthand notation for simple, single-type argument concepts

##### Reason

Readability. Direct expression of an idea.

##### Example (using TS concepts)

To say "`T` is `Sortable`":

```cpp
template<typename T>       // Correct but verbose: "The parameter is
//    requires Sortable<T>   // of type T which is the name of a type
void sort(T&);             // that is Sortable"

template<Sortable T>       // Better (assuming support for concepts): "The parameter is of type T
void sort(T&);             // which is Sortable"

void sort(Sortable&);      // Best (assuming support for concepts): "The parameter is Sortable"

```
The shorter versions better match the way we speak. Note that many templates don't need to use the `template` keyword.

##### Note

"Concepts" are defined in an ISO Technical specification: [concepts](http://www.open-std.org/jtc1/sc22/wg21/docs/papers/2015/n4553.pdf).
A draft of a set of standard-library concepts can be found in another ISO TS: [ranges](http://www.open-std.org/jtc1/sc22/wg21/docs/papers/2016/n4569.pdf)
Currently (July 2016), concepts are supported only in GCC 6.1.
Consequently, we comment out uses of concepts in examples; that is, we use them as formalized comments only.
If you use a compiler that supports concepts (e.g., GCC 6.1), you can remove the `//`.

##### Enforcement

* Not feasible in the short term when people convert from the `<typename T>` and `<class T`> notation.
* Later, flag declarations that first introduces a typename and then constrains it with a simple, single-type-argument concept.

## <a name="SS-concepts-def"></a>T.concepts.def: Concept definition rules

Defining good concepts is non-trivial.
Concepts are meant to represent fundamental concepts in an application domain (hence the name "concepts").
Similarly throwing together a set of syntactic constraints to be used for a the arguments for a single class or algorithm is not what concepts were designed for
and will not give the full benefits of the mechanism.

Obviously, defining concepts will be most useful for code that can use an implementation (e.g., GCC 6.1),
but defining concepts is in itself a useful design technique and help catch conceptual errors and clean up the concepts (sic!) of an implementation.

