### <a name="Rt-std-concepts"></a>T.11: Whenever possible use standard concepts

##### Reason

 "Standard" concepts (as provided by the [GSL](#S-GSL) and the [Ranges TS](http://www.open-std.org/jtc1/sc22/wg21/docs/papers/2016/n4569.pdf), and hopefully soon the ISO standard itself)
saves us the work of thinking up our own concepts, are better thought out than we can manage to do in a hurry, and improves interoperability.

##### Note

Unless you are creating a new generic library, most of the concepts you need will already be defined by the standard library.

##### Example (using TS concepts)

```cpp
template<typename T>
    // don't define this: Sortable is in the GSL
concept Ordered_container = Sequence<T> && Random_access<Iterator<T>> && Ordered<Value_type<T>>;

void sort(Ordered_container& s);

```
This `Ordered_container` is quite plausible, but it is very similar to the `Sortable` concept in the GSL (and the Range TS).
Is it better? Is it right? Does it accurately reflect the standard's requirements for `sort`?
It is better and simpler just to use `Sortable`:

```cpp
void sort(Sortable& s);   // better

```
##### Note

The set of "standard" concepts is evolving as we approach an ISO standard including concepts.

##### Note

Designing a useful concept is challenging.

##### Enforcement

Hard.

* Look for unconstrained arguments, templates that use "unusual"/non-standard concepts, templates that use "homebrew" concepts without axioms.
* Develop a concept-discovery tool (e.g., see [an early experiment](http://www.stroustrup.com/sle2010_webversion.pdf)).

