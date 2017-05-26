### <a name="Rt-use"></a>T.26: Prefer to define concepts in terms of use-patterns rather than simple syntax

##### Reason

The definition is more readable and corresponds directly to what a user has to write.
Conversions are taken into account. You don't have to remember the names of all the type traits.

##### Example (using TS concepts)

You might be tempted to define a concept `Equality` like this:

```cpp
template<typename T> concept Equality = has_equal<T> && has_not_equal<T>;

```
Obviously, it would be better and easier just to use the standard `EqualityComparable`,
but - just as an example - if you had to define such a concept, prefer:

```cpp
template<typename T> concept Equality = requires(T a, T b) {
    bool == { a == b }
    bool == { a != b }
    // axiom { !(a == b) == (a != b) }
    // axiom { a = b; => a == b }  // => means "implies"
}

```
as opposed to defining two meaningless concepts `has_equal` and `has_not_equal` just as helpers in the definition of `Equality`.
By "meaningless" we mean that we cannot specify the semantics of `has_equal` in isolation.

##### Enforcement

???

## <a name="SS-temp-interface"></a>Template interfaces

Over the years, programming with templates have suffered from a weak distinction between the interface of a template
and its implementation.
Before concepts, that distinction had no direct language support.
However, the interface to a template is a critical concept - a contract between a user and an implementer - and should be carefully designed.

