### <a name="Re-never-fail"></a>E.16: Destructors, deallocation, and `swap` must never fail

##### Reason

We don't know how to write reliable programs if a destructor, a swap, or a memory deallocation fails; that is, if it exits by an exception or simply doesn't perform its required action.

##### Example, don't

```cpp
class Connection {
    // ...
public:
    ~Connection()   // Don't: very bad destructor
    {
        if (cannot_disconnect()) throw I_give_up{information};
        // ...
    }
};

```
##### Note

Many have tried to write reliable code violating this rule for examples, such as a network connection that "refuses to close".
To the best of our knowledge nobody has found a general way of doing this.
Occasionally, for very specific examples, you can get away with setting some state for future cleanup.
For example, we might put a socket that does not want to close on a "bad socket" list,
to be examined by a regular sweep of the system state.
Every example we have seen of this is error-prone, specialized, and often buggy.

##### Note

The standard library assumes that destructors, deallocation functions (e.g., `operator delete`), and `swap` do not throw. If they do, basic standard library invariants are broken.

##### Note

Deallocation functions, including `operator delete`, must be `noexcept`. `swap` functions must be `noexcept`.
Most destructors are implicitly `noexcept` by default.
Also, [make move operations `noexcept`](##Rc-move-noexcept).

##### Enforcement

Catch destructors, deallocation operations, and `swap`s that `throw`.
Catch such operations that are not `noexcept`.

**See also**: [discussion](I-28-Discussion-Discussion.md#Sd-never-fail)

