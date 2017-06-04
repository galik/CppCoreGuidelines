### <a name="Rconc-tools"></a>CP.9: Whenever feasible use tools to validate your concurrent code

Experience shows that concurrent code is exceptionally hard to get right
and that compile-time checking, run-time checks, and testing are less effective at finding concurrency errors
than they are at finding errors in sequential code.
Subtle concurrency errors can have dramatically bad effects, including memory corruption and deadlocks.

##### Example

    ???

##### Note

Thread safety is challenging, often getting the better of experienced programmers: tooling is an important strategy to mitigate those risks.
There are many tools "out there", both commercial and open-source tools, both research and production tools.
Unfortunately people's needs and constraints differ so dramatically that we cannot make specific recommendations,
but we can mention:

* Static enforcement tools: both [clang](http://clang.llvm.org/docs/ThreadSafetyAnalysis.html)
and some older versions of [GCC](https://gcc.gnu.org/wiki/ThreadSafetyAnnotation)
have some support for static annotation of thread safety properties.
Consistent use of this technique turns many classes of thread-safety errors into compile-time errors.
The annotations are generally local (marking a particular member variable as guarded by a particular mutex),
and are usually easy to learn. However, as with many static tools, it can often present false negatives;
cases that should have been caught but were allowed.

* dynamic enforcement tools: Clang's [Thread Sanitizer](http://clang.llvm.org/docs/ThreadSanitizer.html) (aka TSAN)
is a powerful example of dynamic tools: it changes the build and execution of your program to add bookkeeping on memory access,
absolutely identifying data races in a given execution of your binary.
The cost for this is both memory (5-10x in most cases) and CPU slowdown (2-20x).
Dynamic tools like this are best when applied to integration tests, canary pushes, or unittests that operate on multiple threads.
Workload matters: When TSAN identifies a problem, it is effectively always an actual data race,
but it can only identify races seen in a given execution.

##### Enforcement

It is up to an application builder to choose which support tools are valuable for a particular applications.

## <a name="SScp-con"></a>CP.con: Concurrency

This section focuses on relatively ad-hoc uses of multiple threads communicating through shared data.

* For parallel algorithms, see [parallelism](I-12-Concurrency%20and%20Parallelism-P.050.md#SScp-par)
* For inter-task communication without explicit sharing, see [messaging](I-12-Concurrency%20and%20Parallelism-P.050.md#SScp-mess)
* For vector parallel code, see [vectorization](I-12-Concurrency%20and%20Parallelism-CP.061.md#SScp-vec)
* For lock-free programming, see [lock free](I-12-Concurrency%20and%20Parallelism-CP.061.md#SScp-free)

Concurrency rule summary:

* [CP.20: Use RAII, never plain `lock()`/`unlock()`](I-12-Concurrency%20and%20Parallelism-CP.020.md#Rconc-raii)
* [CP.21: Use `std::lock()` or `std::scoped_lock` to acquire multiple `mutex`es](I-12-Concurrency%20and%20Parallelism-CP.021.md#Rconc-lock)
* [CP.22: Never call unknown code while holding a lock (e.g., a callback)](I-12-Concurrency%20and%20Parallelism-CP.022.md#Rconc-unknown)
* [CP.23: Think of a joining `thread` as a scoped container](I-12-Concurrency%20and%20Parallelism-CP.023.md#Rconc-join)
* [CP.24: Think of a `thread` as a global container](I-12-Concurrency%20and%20Parallelism-CP.024.md#Rconc-detach)
* [CP.25: Prefer `gsl::joining_thread` over `std::thread`](I-12-Concurrency%20and%20Parallelism-CP.025.md#Rconc-joining_thread)
* [CP.26: Don't `detach()` a thread](I-12-Concurrency%20and%20Parallelism-CP.026.md#Rconc-detached_thread)
* [CP.31: Pass small amounts of data between threads by value, rather than by reference or pointer](I-12-Concurrency%20and%20Parallelism-CP.031.md#Rconc-data-by-value)
* [CP.32: To share ownership between unrelated `thread`s use `shared_ptr`](I-12-Concurrency%20and%20Parallelism-%5BCP.032.md#Rconc-shared)
* [CP.40: Minimize context switching](I-12-Concurrency%20and%20Parallelism-CP.040.md#Rconc-switch)
* [CP.41: Minimize thread creation and destruction](I-12-Concurrency%20and%20Parallelism-CP.041.md#Rconc-create)
* [CP.42: Don't `wait` without a condition](I-12-Concurrency%20and%20Parallelism-CP.042.md#Rconc-wait)
* [CP.43: Minimize time spent in a critical section](I-12-Concurrency%20and%20Parallelism-CP.043.md#Rconc-time)
* [CP.44: Remember to name your `lock_guard`s and `unique_lock`s](I-12-Concurrency%20and%20Parallelism-CP.044.md#Rconc-name)
* [CP.50: Define a `mutex` together with the data it protects](I-12-Concurrency%20and%20Parallelism-P.050.md#Rconc-mutex)
* ??? when to use a spinlock
* ??? when to use `try_lock()`
* ??? when to prefer `lock_guard` over `unique_lock`
* ??? Time multiplexing
* ??? when/how to use `new thread`

