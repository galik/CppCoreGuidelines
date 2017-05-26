### <a name="Ri-concepts"></a>I.9: If an interface is a template, document its parameters using concepts

##### Reason

Make the interface precisely specified and compile-time checkable in the (not so distant) future.

##### Example

Use the ISO Concepts TS style of requirements specification. For example:

```cpp
template<typename Iter, typename Val>
// requires InputIterator<Iter> && EqualityComparable<ValueType<Iter>>, Val>
Iter find(Iter first, Iter last, Val v)
{
    // ...
}

```
##### Note

Soon (maybe in 2017), most compilers will be able to check `requires` clauses once the `//` is removed.
For now, the concept TS is supported only in GCC 6.1.

**See also**: [Generic programming](I-15-Templates%20and%20generic%20programming.md#SS-GP) and [concepts](#SS-t-concepts).

##### Enforcement

(Not yet enforceable) A language facility is under specification. When the language facility is available, warn if any non-variadic template parameter is not constrained by a concept (in its declaration or mentioned in a `requires` clause).

