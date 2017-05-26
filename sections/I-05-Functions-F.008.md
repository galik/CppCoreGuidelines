### <a name="Rf-pure"></a>F.8: Prefer pure functions

##### Reason

Pure functions are easier to reason about, sometimes easier to optimize (and even parallelize), and sometimes can be memoized.

##### Example

```cpp
template<class T>
auto square(T t) { return t * t; }

```
##### Note

`constexpr` functions are pure.

When given a non-constant argument, a `constexpr` function can throw.
If you consider exiting by throwing a side-effect, a `constexpr` function isn't completely pure;
if not, this is not an issue.
??? A question for the committee: can a constructor for an exception thrown by a `constexpr` function modify state?
"No" would be a nice answer that matches most practice.

##### Enforcement

Not possible.

