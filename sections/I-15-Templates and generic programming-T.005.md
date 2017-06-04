### <a name="Rt-generic-oo"></a>T.5: Combine generic and OO techniques to amplify their strengths, not their costs

##### Reason

Generic and OO techniques are complementary.

##### Example

Static helps dynamic: Use static polymorphism to implement dynamically polymorphic interfaces.

```cpp
class Command {
    // pure virtual functions
};

// implementations
template</*...*/>
class ConcreteCommand : public Command {
    // implement virtuals
};

```
##### Example

Dynamic helps static: Offer a generic, comfortable, statically bound interface, but internally dispatch dynamically, so you offer a uniform object layout.
Examples include type erasure as with `std::shared_ptr`'s deleter (but [don't overuse type erasure](I-15-Templates%20and%20generic%20programming-T.049.md#Rt-erasure)).

##### Note

In a class template, nonvirtual functions are only instantiated if they're used -- but virtual functions are instantiated every time.
This can bloat code size, and may overconstrain a generic type by instantiating functionality that is never needed.
Avoid this, even though the standard-library facets made this mistake.

##### See also

* ref ???
* ref ???
* ref ???

##### Enforcement

See the reference to more specific rules.

## <a name="SS-concepts"></a>T.concepts: Concept rules

Concepts is a facility for specifying requirements for template arguments.
It is an [ISO technical specification](#Ref-conceptsTS), but currently supported only by GCC.
Concepts are, however, crucial in the thinking about generic programming and the basis of much work on future C++ libraries
(standard and other).

This section assumes concept support

Concept use rule summary:

* [T.10: Specify concepts for all template arguments](I-15-Templates%20and%20generic%20programming-T.010.md#Rt-concepts)
* [T.11: Whenever possible use standard concepts](I-15-Templates%20and%20generic%20programming-T.011.md#Rt-std-concepts)
* [T.12: Prefer concept names over `auto`](I-15-Templates%20and%20generic%20programming-T.012.md#Rt-auto)
* [T.13: Prefer the shorthand notation for simple, single-type argument concepts](I-15-Templates%20and%20generic%20programming-T.013.md#Rt-shorthand)
* ???

Concept definition rule summary:

* [T.20: Avoid "concepts" without meaningful semantics](I-15-Templates%20and%20generic%20programming-T.020.md#Rt-low)
* [T.21: Require a complete set of operations for a concept](#Rt-complete)
* [T.22: Specify axioms for concepts](I-15-Templates%20and%20generic%20programming-T.022.md#Rt-axiom)
* [T.23: Differentiate a refined concept from its more general case by adding new use patterns](I-15-Templates%20and%20generic%20programming-T.023.md#Rt-refine)
* [T.24: Use tag classes or traits to differentiate concepts that differ only in semantics](I-15-Templates%20and%20generic%20programming-T.024.md#Rt-tag)
* [T.25: Avoid complimentary constraints](I-15-Templates%20and%20generic%20programming-T.025.md#Rt-not)
* [T.26: Prefer to define concepts in terms of use-patterns rather than simple syntax](I-15-Templates%20and%20generic%20programming-T.026.md#Rt-use)
* ???

## <a name="SS-concept-use"></a>T.con-use: Concept use

