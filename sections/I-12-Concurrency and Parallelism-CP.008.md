### <a name="Rconc-volatile"></a>CP.8: Don't try to use `volatile` for synchronization

##### Reason

In C++, unlike some other languages, `volatile` does not provide atomicity, does not synchronize between threads,
and does not prevent instruction reordering (neither compiler nor hardware).
It simply has nothing to do with concurrency.

##### Example, bad:

```cpp
int free_slots = max_slots; // current source of memory for objects

Pool* use()
{
    if (int n = free_slots--) return &pool[n];
}

```
Here we have a problem:
This is perfectly good code in a single-threaded program, but have two threads execute this and
there is a race condition on `free_slots` so that two threads might get the same value and `free_slots`.
That's (obviously) a bad data race, so people trained in other languages may try to fix it like this:

```cpp
volatile int free_slots = max_slots; // current source of memory for objects

Pool* use()
{
    if (int n = free_slots--) return &pool[n];
}

```
This has no effect on synchronization: The data race is still there!

The C++ mechanism for this is `atomic` types:

```cpp
atomic<int> free_slots = max_slots; // current source of memory for objects

Pool* use()
{
    if (int n = free_slots--) return &pool[n];
}

```
Now the `--` operation is atomic,
rather than a read-increment-write sequence where another thread might get in-between the individual operations.

##### Alternative

Use `atomic` types where you might have used `volatile` in some other language.
Use a `mutex` for more complicated examples.

##### See also

[(rare) proper uses of `volatile`](I-12-Concurrency%20and%20Parallelism-CP.200.md#Rconc-volatile2)

