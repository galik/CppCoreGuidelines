### <a name="Ri-pre"></a>I.5: State preconditions (if any)

##### Reason

Arguments have meaning that may constrain their proper use in the callee.

##### Example

Consider:

```cpp
double sqrt(double x);

```
Here `x` must be nonnegative. The type system cannot (easily and naturally) express that, so we must use other means. For example:

```cpp
double sqrt(double x); // x must be nonnegative

```
Some preconditions can be expressed as assertions. For example:

```cpp
double sqrt(double x) { Expects(x >= 0); /* ... */ }

```
Ideally, that `Expects(x >= 0)` should be part of the interface of `sqrt()` but that's not easily done. For now, we place it in the definition (function body).

**References**: `Expects()` is described in [GSL](I-23-Guideline%20support%20library.md#S-gsl).

##### Note

Prefer a formal specification of requirements, such as `Expects(p != nullptr);`.
If that is infeasible, use English text in comments, such as `// the sequence [p:q) is ordered using <`.

##### Note

Most member functions have as a precondition that some class invariant holds.
That invariant is established by a constructor and must be reestablished upon exit by every member function called from outside the class.
We don't need to mention it for each member function.

##### Enforcement

(Not enforceable)

**See also**: The rules for passing pointers. ???

