# <a name="S-templates"></a>T: Templates and generic programming

Generic programming is programming using types and algorithms parameterized by types, values, and algorithms.
In C++, generic programming is supported by the `template` language mechanisms.

Arguments to generic functions are characterized by sets of requirements on the argument types and values involved.
In C++, these requirements are expressed by compile-time predicates called concepts.

Templates can also be used for meta-programming; that is, programs that compose code at compile time.

A central notion in generic programming is "concepts"; that is, requirements on template arguments presented as compile-time predicates.
"Concepts" are defined in an ISO Technical specification: [concepts](http://www.open-std.org/jtc1/sc22/wg21/docs/papers/2015/n4553.pdf).
A draft of a set of standard-library concepts can be found in another ISO TS: [ranges](http://www.open-std.org/jtc1/sc22/wg21/docs/papers/2016/n4569.pdf)
Currently (July 2016), concepts are supported only in GCC 6.1.
Consequently, we comment out uses of concepts in examples; that is, we use them as formalized comments only.
If you use GCC 6.1, you can uncomment them.

Template use rule summary:

* [T.1: Use templates to raise the level of abstraction of code](I-15-Templates and generic programming-T.001.md#Rt-raise)
* [T.2: Use templates to express algorithms that apply to many argument types](I-15-Templates and generic programming-T.002.md#Rt-algo)
* [T.3: Use templates to express containers and ranges](I-15-Templates and generic programming-T.003.md#Rt-cont)
* [T.4: Use templates to express syntax tree manipulation](I-15-Templates and generic programming-T.004.md#Rt-expr)
* [T.5: Combine generic and OO techniques to amplify their strengths, not their costs](I-15-Templates and generic programming-T.005.md#Rt-generic-oo)

Concept use rule summary:

* [T.10: Specify concepts for all template arguments](I-15-Templates and generic programming-T.010.md#Rt-concepts)
* [T.11: Whenever possible use standard concepts](I-15-Templates and generic programming-T.011.md#Rt-std-concepts)
* [T.12: Prefer concept names over `auto` for local variables](I-15-Templates and generic programming-T.012.md#Rt-auto)
* [T.13: Prefer the shorthand notation for simple, single-type argument concepts](I-15-Templates and generic programming-T.013.md#Rt-shorthand)
* ???

Concept definition rule summary:

* [T.20: Avoid "concepts" without meaningful semantics](I-15-Templates and generic programming-T.020.md#Rt-low)
* [T.21: Require a complete set of operations for a concept](#Rt-complete)
* [T.22: Specify axioms for concepts](I-15-Templates and generic programming-T.022.md#Rt-axiom)
* [T.23: Differentiate a refined concept from its more general case by adding new use patterns](I-15-Templates and generic programming-T.023.md#Rt-refine)
* [T.24: Use tag classes or traits to differentiate concepts that differ only in semantics](I-15-Templates and generic programming-T.024.md#Rt-tag)
* [T.25: Avoid complementary constraints](I-15-Templates and generic programming-T.025.md#Rt-not)
* [T.26: Prefer to define concepts in terms of use-patterns rather than simple syntax](I-15-Templates and generic programming-T.026.md#Rt-use)
* [T.30: Use concept negation (`!C<T>`) sparingly to express a minor difference](I-15-Templates and generic programming-T.025.md#Rt-not)
* [T.31: Use concept disjunction (`C1<T> || C2<T>`) sparingly to express alternatives](#Rt-or)
* ???

Template interface rule summary:

* [T.40: Use function objects to pass operations to algorithms](I-15-Templates and generic programming-T.040.md#Rt-fo)
* [T.41: Require only essential properties in a template's concepts](I-15-Templates and generic programming-T.041.md#Rt-essential)
* [T.42: Use template aliases to simplify notation and hide implementation details](I-15-Templates and generic programming-T.042.md#Rt-alias)
* [T.43: Prefer `using` over `typedef` for defining aliases](I-15-Templates and generic programming-T.043.md#Rt-using)
* [T.44: Use function templates to deduce class template argument types (where feasible)](I-15-Templates and generic programming-T.044.md#Rt-deduce)
* [T.46: Require template arguments to be at least `Regular` or `SemiRegular`](I-15-Templates and generic programming-T.046.md#Rt-regular)
* [T.47: Avoid highly visible unconstrained templates with common names](I-15-Templates and generic programming-T.047.md#Rt-visible)
* [T.48: If your compiler does not support concepts, fake them with `enable_if`](I-15-Templates and generic programming-T.048.md#Rt-concept-def)
* [T.49: Where possible, avoid type-erasure](I-15-Templates and generic programming-T.049.md#Rt-erasure)

Template definition rule summary:

* [T.60: Minimize a template's context dependencies](I-15-Templates and generic programming-T.060.md#Rt-depend)
* [T.61: Do not over-parameterize members (SCARY)](I-15-Templates and generic programming-T.061.md#Rt-scary)
* [T.62: Place non-dependent class template members in a non-templated base class](I-15-Templates and generic programming-T.062.md#Rt-nondependent)
* [T.64: Use specialization to provide alternative implementations of class templates](I-15-Templates and generic programming-T.064.md#Rt-specialization)
* [T.65: Use tag dispatch to provide alternative implementations of functions](I-15-Templates and generic programming-T.065.md#Rt-tag-dispatch)
* [T.67: Use specialization to provide alternative implementations for irregular types](I-15-Templates and generic programming-T.067.md#Rt-specialization2)
* [T.68: Use `{}` rather than `()` within templates to avoid ambiguities](I-15-Templates and generic programming-T.068.md#Rt-cast)
* [T.69: Inside a template, don't make an unqualified nonmember function call unless you intend it to be a customization point](I-15-Templates and generic programming-T.069.md#Rt-customization)

Template and hierarchy rule summary:

* [T.80: Do not naively templatize a class hierarchy](I-15-Templates and generic programming-T.080.md#Rt-hier)
* [T.81: Do not mix hierarchies and arrays](I-15-Templates and generic programming-T.081.md#Rt-array) // ??? somewhere in "hierarchies"
* [T.82: Linearize a hierarchy when virtual functions are undesirable](I-15-Templates and generic programming-T.082.md#Rt-linear)
* [T.83: Do not declare a member function template virtual](I-15-Templates and generic programming-T.083.md#Rt-virtual)
* [T.84: Use a non-template core implementation to provide an ABI-stable interface](I-15-Templates and generic programming-T.084.md#Rt-abi)
* [T.??: ????](#Rt-???)

Variadic template rule summary:

* [T.100: Use variadic templates when you need a function that takes a variable number of arguments of a variety of types](I-15-Templates and generic programming-T.100.md#Rt-variadic)
* [T.101: ??? How to pass arguments to a variadic template ???](I-15-Templates and generic programming-T.101.md#Rt-variadic-pass)
* [T.102: ??? How to process arguments to a variadic template ???](I-15-Templates and generic programming-T.102.md#Rt-variadic-process)
* [T.103: Don't use variadic templates for homogeneous argument lists](I-15-Templates and generic programming-T.103.md#Rt-variadic-not)
* [T.??: ????](#Rt-???)

Metaprogramming rule summary:

* [T.120: Use template metaprogramming only when you really need to](I-15-Templates and generic programming-T.120.md#Rt-metameta)
* [T.121: Use template metaprogramming primarily to emulate concepts](I-15-Templates and generic programming-T.121.md#Rt-emulate)
* [T.122: Use templates (usually template aliases) to compute types at compile time](I-15-Templates and generic programming-T.122.md#Rt-tmp)
* [T.123: Use `constexpr` functions to compute values at compile time](I-15-Templates and generic programming-T.123.md#Rt-fct)
* [T.124: Prefer to use standard-library TMP facilities](I-15-Templates and generic programming-T.124.md#Rt-std-tmp)
* [T.125: If you need to go beyond the standard-library TMP facilities, use an existing library](I-15-Templates and generic programming-T.125.md#Rt-lib)
* [T.??: ????](#Rt-???)

Other template rules summary:

* [T.140: Name all operations with potential for reuse](I-15-Templates and generic programming-T.140.md#Rt-name)
* [T.141: Use an unnamed lambda if you need a simple function object in one place only](I-15-Templates and generic programming-T.141.md#Rt-lambda)
* [T.142: Use template variables to simplify notation](I-15-Templates and generic programming-T.142?.md#Rt-var)
* [T.143: Don't write unintentionally nongeneric code](I-15-Templates and generic programming-T.143.md#Rt-nongeneric)
* [T.144: Don't specialize function templates](I-15-Templates and generic programming-T.144.md#Rt-specialize-function)
* [T.150: Check that a class matches a concept using `static_assert`](I-15-Templates and generic programming-T.150.md#Rt-check-class)
* [T.??: ????](#Rt-???)

## <a name="SS-GP"></a>T.gp: Generic programming

Generic programming is programming using types and algorithms parameterized by types, values, and algorithms.

