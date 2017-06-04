### <a name="Ri-nargs"></a>I.23: Keep the number of function arguments low

##### Reason

Having many arguments opens opportunities for confusion. Passing lots of arguments is often costly compared to alternatives.

##### Discussion

The two most common reasons why functions have too many parameters are:

    1. *Missing an abstraction.* There is an abstraction missing, so that a compound value is being
    passed as individual elements instead of as a single object that enforces an invariant.
    This not only expands the parameter list, but it leads to errors because the component values
    are no longer protected by an enforced invariant.

    2. *Violating "one function, one responsibility."* The function is trying to do more than one
    job and should probably be refactored.

##### Example

The standard-library `merge()` is at the limit of what we can comfortably handle:

    template<class InputIterator1, class InputIterator2, class OutputIterator, class Compare>
    OutputIterator merge(InputIterator1 first1, InputIterator1 last1,
                         InputIterator2 first2, InputIterator2 last2,
                         OutputIterator result, Compare comp);

Note that this is because of problem 1 above -- missing abstraction. Instead of passing a range (abstraction), STL passed iterator pairs (unencapsulated component values).

Here, we have four template arguments and six function arguments.
To simplify the most frequent and simplest uses, the comparison argument can be defaulted to `<`:

    template<class InputIterator1, class InputIterator2, class OutputIterator>
    OutputIterator merge(InputIterator1 first1, InputIterator1 last1,
                         InputIterator2 first2, InputIterator2 last2,
                         OutputIterator result);

This doesn't reduce the total complexity, but it reduces the surface complexity presented to many users.
To really reduce the number of arguments, we need to bundle the arguments into higher-level abstractions:

    template<class InputRange1, class InputRange2, class OutputIterator>
    OutputIterator merge(InputRange1 r1, InputRange2 r2, OutputIterator result);

Grouping arguments into "bundles" is a general technique to reduce the number of arguments and to increase the opportunities for checking.

Alternatively, we could use concepts (as defined by the ISO TS) to define the notion of three types that must be usable for merging:

    Mergeable{In1 In2, Out}
    OutputIterator merge(In1 r1, In2 r2, Out result);

##### Example

The safety Profiles recommend replacing

    void f(int* some_ints, int some_ints_length);  // BAD: C style, unsafe

with

    void f(gsl::span<int> some_ints);              // GOOD: safe, bounds-checked

Here, using an abstraction has safety and robustness benefits, and naturally also reduces the number of parameters.

##### Note

How many parameters are too many? Try to use fewer than four (4) parameters.
There are functions that are best expressed with four individual parameters, but not many.

**Alternative**: Use better abstraction: Group arguments into meaningful objects and pass the objects (by value or by reference).

**Alternative**: Use default arguments or overloads to allow the most common forms of calls to be done with fewer arguments.

##### Enforcement

* Warn when a function declares two iterators (including pointers) of the same type instead of a range or a view.
* (Not enforceable) This is a philosophical guideline that is infeasible to check directly.

