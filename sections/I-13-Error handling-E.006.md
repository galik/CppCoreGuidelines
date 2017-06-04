### <a name="Re-raii"></a>E.6: Use RAII to prevent leaks

##### Reason

Leaks are typically unacceptable.
Manual resource release is error-prone.
RAII ("Resource Acquisition Is Initialization") is the simplest, most systematic way of preventing leaks.

##### Example

```cpp
void f1(int i)   // Bad: possibly leak
{
    int* p = new int[12];
    // ...
    if (i < 17) throw Bad {"in f()", i};
    // ...
}

```
We could carefully release the resource before the throw:

```cpp
void f2(int i)   // Clumsy and error-prone: explicit release
{
    int* p = new int[12];
    // ...
    if (i < 17) {
        delete[] p;
        throw Bad {"in f()", i};
    }
    // ...
}

```
This is verbose. In larger code with multiple possible `throw`s explicit releases become repetitive and error-prone.

```cpp
void f3(int i)   // OK: resource management done by a handle (but see below)
{
    auto p = make_unique<int[]>(12);
    // ...
    if (i < 17) throw Bad {"in f()", i};
    // ...
}

```
Note that this works even when the `throw` is implicit because it happened in a called function:

```cpp
void f4(int i)   // OK: resource management done by a handle (but see below)
{
    auto p = make_unique<int[]>(12);
    // ...
    helper(i);   // may throw
    // ...
}

```
Unless you really need pointer semantics, use a local resource object:

```cpp
void f5(int i)   // OK: resource management done by local object
{
    vector<int> v(12);
    // ...
    helper(i);   // may throw
    // ...
}

```
That's even simpler and safer, and often more efficient.

##### Note

If there is no obvious resource handle and for some reason defining a proper RAII object/handle is infeasible,
as a last resort, cleanup actions can be represented by a [`final_action`](I-13-Error%20handling-E.019.md#Re-finally) object.

##### Note

But what do we do if we are writing a program where exceptions cannot be used?
First challenge that assumption; there are many anti-exceptions myths around.
We know of only a few good reasons:

* We are on a system so small that the exception support would eat up most of our 2K memory.
* We are in a hard-real-time system and we don't have tools that guarantee us that an exception is handled within the required time.
* We are in a system with tons of legacy code using lots of pointers in difficult-to-understand ways
  (in particular without a recognizable ownership strategy) so that exceptions could cause leaks.
* Our implementation of the C++ exception mechanisms is unreasonably poor
(slow, memory consuming, failing to work correctly for dynamically linked libraries, etc.).
Complain to your implementation purveyor; if no user complains, no improvement will happen.
* We get fired if we challenge our manager's ancient wisdom.

Only the first of these reasons is fundamental, so whenever possible, use exceptions to implement RAII, or design your RAII objects to never fail.
When exceptions cannot be used, simulate RAII.
That is, systematically check that objects are valid after construction and still release all resources in the destructor.
One strategy is to add a `valid()` operation to every resource handle:

```cpp
void f()
{
    vector<string> vs(100);   // not std::vector: valid() added
    if (!vs.valid()) {
        // handle error or exit
    }

    ifstream fs("foo");   // not std::ifstream: valid() added
    if (!fs.valid()) {
        // handle error or exit
    }

    // ...
} // destructors clean up as usual

```
Obviously, this increases the size of the code, doesn't allow for implicit propagation of "exceptions" (`valid()` checks), and `valid()` checks can be forgotten.
Prefer to use exceptions.

**See also**: [Use of `noexcept`](#Se-noexcept).

##### Enforcement

???

