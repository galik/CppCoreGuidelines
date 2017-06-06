### <a name="Rconc-lock"></a>CP.21: Use `std::lock()` or `std::scoped_lock` to acquire multiple `mutex`es

##### Reason

To avoid deadlocks on multiple `mutex`es.

##### Example

This is asking for deadlock:

```cpp
// thread 1
lock_guard<mutex> lck1(m1);
lock_guard<mutex> lck2(m2);

// thread 2
lock_guard<mutex> lck2(m2);
lock_guard<mutex> lck1(m1);

```
Instead, use `lock()`:

```cpp
// thread 1
lock(lck1, lck2);
lock_guard<mutex> lck1(m1, adopt_lock);
lock_guard<mutex> lck2(m2, adopt_lock);

// thread 2
lock(lck2, lck1);
lock_guard<mutex> lck2(m2, adopt_lock);
lock_guard<mutex> lck1(m1, adopt_lock);

```
or (better, but C++17 only):

```cpp
// thread 1
scoped_lock<mutex, mutex> lck1(m1, m2);

// thread 2
scoped_lock<mutex, mutex> lck2(m2, m1);

```
Here, the writers of `thread1` and `thread2` are still not agreeing on the order of the `mutex`es, but order no longer matters.

##### Note

In real code, `mutex`es are rarely named to conveniently remind the programmer of an intended relation and intended order of acquisition.
In real code, `mutex`es are not always conveniently acquired on consecutive lines.

In C++17 it's possible to write plain

```cpp
lock_guard lck1(m1, adopt_lock);

```
and have the `mutex` type deduced.

##### Enforcement

Detect the acquisition of multiple `mutex`es.
This is undecidable in general, but catching common simple examples (like the one above) is easy.


