### <a name="Re-specifications"></a>E.30: Don't use exception specifications

##### Reason

Exception specifications make error handling brittle, impose a run-time cost, and have been removed from the C++ standard.

##### Example

```cpp
int use(int arg)
    throw(X, Y)
{
    // ...
    auto x = f(arg);
    // ...
}

```
if `f()` throws an exception different from `X` and `Y` the unexpected handler is invoked, which by default terminates.
That's OK, but say that we have checked that this cannot happen and `f` is changed to throw a new exception `Z`,
we now have a crash on our hands unless we change `use()` (and re-test everything).
The snag is that `f()` may be in a library we do not control and the new exception is not anything that `use()` can do
anything about or is in any way interested in.
We can change `use()` to pass `Z` through, but now `use()`'s callers probably needs to be modified.
This quickly becomes unmanageable.
Alternatively, we can add a `try`-`catch` to `use()` to map `Z` into an acceptable exception.
This too, quickly becomes unmanageable.
Note that changes to the set of exceptions often happens at the lowest level of a system
(e.g., because of changes to a network library or some middleware), so changes "bubble up" through long call chains.
In a large code base, this could mean that nobody could update to a new version of a library until the last user was modified.
If `use()` is part of a library, it may not be possible to update it because a change could affect unknown clients.

The policy of letting exceptions propagate until they reach a function that potentially can handle it has proven itself over the years.

##### Note

No. This would not be any better had exception specifications been statically enforced.
For example, see [Stroustrup94](I-31-Bibliography.md#Stroustrup94).

##### Note

If no exception may be thrown, use [`noexcept`](I-13-Error handling-E.012.md#Re-noexcept) or its equivalent `throw()`.

##### Enforcement

Flag every exception specification.

