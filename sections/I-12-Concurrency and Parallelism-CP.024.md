### <a name="Rconc-detach"></a>CP.24: Think of a `thread` as a global container

##### Reason

To maintain pointer safety and avoid leaks, we need to consider what pointers are used by a `thread`.
If a `thread` is detached, we can safely pass pointers to static and free store objects (only).

##### Example

```cpp
void f(int* p)
{
    // ...
    *p = 99;
    // ...
}

int glob = 33;

void some_fct(int* p)
{
    int x = 77;
    std::thread t0(f, &x);           // bad
    std::thread t1(f, p);            // bad
    std::thread t2(f, &glob);        // OK
    auto q = make_unique<int>(99);
    std::thread t3(f, q.get());      // bad
    // ...
    t0.detach();
    t1.detach();
    t2.detach();
    t3.detach();
    // ...
}

```
By "OK" we mean that the object will be in scope ("live") for as long as a `thread` can use the pointers to it.
By "bad" we mean that a `thread` may use a pointer after the pointed-to object is destroyed.
The fact that `thread`s run concurrently doesn't affect the lifetime or ownership issues here;
these `thread`s can be seen as just a function object called from `some_fct`.

##### Note

Even objects with static storage duration can be problematic if used from detached threads: if the
thread continues until the end of the program, it might be running concurrently with the destruction
of objects with static storage duration, and thus accesses to such objects might race.

##### Note

This rule is redundant if you [don't `detach()`](I-12-Concurrency%20and%20Parallelism-CP.026.md#Rconc-detached_thread) and [use `gsl::joining_thread`](I-12-Concurrency%20and%20Parallelism-CP.025.md#Rconc-joining_thread).
However, converting code to follow those guidelines could be difficult and even impossible for third-party libraries.
In such cases, the rule becomes essential for lifetime safety and type safety.


In general, it is undecidable whether a `detach()` is executed for a `thread`, but simple common cases are easily detected.
If we cannot prove that a `thread` does not `detach()`, we must assume that it does and that it outlives the scope in which it was constructed;
After that, the usual lifetime and ownership (for global objects) enforcement applies.

##### Enforcement

Flag attempts to pass local variables to a thread that might `detach()`.

