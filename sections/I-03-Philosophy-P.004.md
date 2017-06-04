### <a name="Rp-typesafe"></a>P.4: Ideally, a program should be statically type safe

##### Reason

Ideally, a program would be completely statically (compile-time) type safe.
Unfortunately, that is not possible. Problem areas:

* unions
* casts
* array decay
* range errors
* narrowing conversions

##### Note

These areas are sources of serious problems (e.g., crashes and security violations).
We try to provide alternative techniques.

##### Enforcement

We can ban, restrain, or detect the individual problem categories separately, as required and feasible for individual programs.
Always suggest an alternative.
For example:

* unions -- use `variant` (in C++17)
* casts -- minimize their use; templates can help
* array decay -- use `span` (from the GSL)
* range errors -- use `span`
* narrowing conversions -- minimize their use and use `narrow` or `narrow_cast` (from the GSL) where they are necessary

