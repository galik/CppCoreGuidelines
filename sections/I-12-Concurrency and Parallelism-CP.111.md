### <a name="Rconc-double-pattern"></a>CP.111: Use a conventional pattern if you really need double-checked locking

##### Reason

Double-checked locking is easy to mess up. If you really need to write your own double-checked locking, in spite of the rules [CP.110: Do not write your own double-checked locking for initialization](I-12-Concurrency and Parallelism-CP.110.md#Rconc-double) and [CP.100: Don't use lock-free programming unless you absolutely have to](I-12-Concurrency and Parallelism-CP.100.md#Rconc-lockfree), then do it in a conventional pattern.

The uses of the double-checked locking pattern that are not in violation of [CP.110: Do not write your own double-checked locking for initialization](I-12-Concurrency and Parallelism-CP.110.md#Rconc-double) arise when a non-thread-safe action is both hard and rare, and there exists a fast thread-safe test that can be used to guarantee that the action is not needed, but cannot be used to guarantee the converse.

##### Example, bad

The use of volatile does not make the first check thread-safe, see also [CP.200: Use `volatile` only to talk to non-C++ memory](I-12-Concurrency and Parallelism-CP.200.md#Rconc-volatile2)

```cpp
mutex action_mutex;
volatile bool action_needed;

if (action_needed) {
    std::lock_guard<std::mutex> lock(action_mutex);
    if (action_needed) {
        take_action();
        action_needed = false;
    }
}

```
##### Example, good

```cpp
mutex action_mutex;
atomic<bool> action_needed;

if (action_needed) {
    std::lock_guard<std::mutex> lock(action_mutex);
    if (action_needed) {
        take_action();
        action_needed = false;
    }
}

```
Fine-tuned memory order may be beneficial where acquire load is more efficient than sequentially-consistent load

```cpp
mutex action_mutex;
atomic<bool> action_needed;

if (action_needed.load(memory_order_acquire)) {
    lock_guard<std::mutex> lock(action_mutex);
    if (action_needed.load(memory_order_relaxed)) {
        take_action();
        action_needed.store(false, memory_order_release);
    }
}

```
##### Enforcement

??? Is it possible to detect the idiom?


## <a name="SScp-etc"></a>CP.etc: Etc. concurrency rules

These rules defy simple categorization:

* [CP.200: Use `volatile` only to talk to non-C++ memory](I-12-Concurrency and Parallelism-CP.200.md#Rconc-volatile2)
* [CP.201: ??? Signals](I-12-Concurrency and Parallelism-CP.201.md#Rconc-signal)

