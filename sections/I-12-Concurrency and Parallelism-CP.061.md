### <a name="Rconc-async"></a>CP.61: Use a `async()` to spawn a concurrent task

##### Reason

A `future` preserves the usual function call return semantics for asynchronous tasks.
The is no explicit locking and both correct (value) return and error (exception) return are handled simply.

##### Example

    ???

##### Note

Unfortunately, `async()` is not perfect.
For example, there is no guarantee that a thread pool is used to minimize thread construction.
In fact, most current `async()` implementations don't.
However, `async()` is simple and logically correct so until something better comes along
and unless you really need to optimize for many asynchronous tasks, stick with `async()`.

##### Enforcement

???


## <a name="SScp-vec"></a>CP.vec: Vectorization

Vectorization is a technique for executing a number of tasks concurrently without introducing explicit synchronization.
An operation is simply applied to elements of a data structure (a vector, an array, etc.) in parallel.
Vectorization has the interesting property of often requiring no non-local changes to a program.
However, vectorization works best with simple data structures and with algorithms specifically crafted to enable it.

Vectorization rule summary:

* ???
* ???

## <a name="SScp-free"></a>CP.free: Lock-free programming

Synchronization using `mutex`es and `condition_variable`s can be relatively expensive.
Furthermore, it can lead to deadlock.
For performance and to eliminate the possibility of deadlock, we sometimes have to use the tricky low-level "lock-free" facilities
that rely on briefly gaining exclusive ("atomic") access to memory.
Lock free programming is also used to implement higher-level concurrency mechanisms, such as `thread`s and `mutex`es.

Lock-free programming rule summary:

* [CP.100: Don't use lock-free programming unless you absolutely have to](I-12-Concurrency%20and%20Parallelism-CP.100.md#Rconc-lockfree)
* [CP.101: Distrust your hardware/compiler combination](I-12-Concurrency%20and%20Parallelism-CP.101.md#Rconc-distrust)
* [CP.102: Carefully study the literature](I-12-Concurrency%20and%20Parallelism-CP.102.md#Rconc-literature)
* how/when to use atomics
* avoid starvation
* use a lock free data structure rather than hand-crafting specific lock-free access
* [CP.110: Do not write your own double-checked locking for initialization](I-12-Concurrency%20and%20Parallelism-CP.110.md#Rconc-double)
* [CP.111: Use a conventional pattern if you really need double-checked locking](I-12-Concurrency%20and%20Parallelism-CP.111.md#Rconc-double-pattern)
* how/when to compare and swap


