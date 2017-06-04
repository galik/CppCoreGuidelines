### <a name="Res-deref"></a>ES.65: Don't dereference an invalid pointer

##### Reason

Dereferencing an invalid pointer, such as `nullptr`, is undefined behavior, typically leading to immediate crashes,
wrong results, or memory corruption.

##### Note

This rule is an obvious and well-known language rule, but can be hard to follow.
It takes good coding style, library support, and static analysis to eliminate violations without major overhead.
This is a major part of the discussion of [C++'s resource- and type-safety model](#Stroustrup15).

See also

* Use [RAII](I-09-Resource%20management-R.001.md#Rr-raii) to avoid lifetime problems.
* Use [unique_ptr](I-05-Functions-F.026.md#Rf-unique_ptr) to avoid lifetime problems.
* Use [shared_ptr](I-05-Functions-F.027.md#Rf-shared_ptr) to avoid lifetime problems.
* Use [references](I-05-Functions-F.060.md#Rf-ptr-ref) when `nulllptr` isn't a possibility.
* Use [not_null](#Rf-not_null) to catch unexpected `nullptr` early.
* Use the [bounds profile](I-22-Profiles.md#SS-bounds) to avoid range errors.


##### Example

```cpp
void f()
{
    int x = 0;
    int* p = &x;

    if (condition()) {
        int y = 0;
        p = &y;
    } // invalidates p

    *p = 42;            // BAD, p might be invalid if the branch was taken
}

```
To resolve the problem, either extend the lifetime of the object the pointer is intended to refer to, or shorten the lifetime of the pointer (move the dereference to before the pointed-to object's lifetime ends).

```cpp
void f1()
{
    int x = 0;
    int* p = &x;

    int y = 0;
    if (condition()) {
        p = &y;
    }

    *p = 42;            // OK, p points to x or y and both are still in scope
}

```
Unfortunately, most invalid pointer problems are harder to spot and harder to fix.

##### Example

```cpp
void f(int* p)
{
    int x = *p; // BAD: how do we know that p is valid?
}

```
There is a huge amount of such code.
Most works -- after lots of testing -- but in isolation it is impossible to tell whether `p` could be the `nullptr`.
Consequently, it this is also a major source of errors.
There are many approaches to dealing with this potential problem:

```cpp
void f1(int* p) // deal with nullptr
{
    if (p==nullptr) {
        // deal with nullptr (allocate, return, throw, make p point to something, whatever
    }
    int x = *p;
}

```
There are two potential problems with testing for `nullptr`:

* it is not always obvious what to do what to do if we find `nullptr`
* the test can be redundant and/or relatively expensive
* it is not obvious if the test is to protect against a violation or part of the required logic.

```cpp
void f2(int* p) // state that p is not supposed to be nullptr
{
    Assert(p!=nullptr);     
    int x = *p;
}

```
This would carry a cost only when the assertion checking was ensbled and would give a compiler/analyser useful information.
This would work even better if/when C++ gets direct support for contracts:

```cpp
void f3(int* p) // state that p is not supposed to be nullptr
    [[expects: p!=nullptr]]
{
    int x = *p;
}

```
Alternatively, we could use `gsl::not_null` to ensure that `p` is not the `nullptr`.

```cpp
void f(not_null<int*> p)
{
    int x = *p;
}

```
There remedies take care of `nullptr` only.
Remember that there are other ways of getting an invalid pointer.

##### Example

```cpp
void f(int* p)  // old code, doesn't use owner
{
    delete p;
}

void g()        // old code: uses naked new
{
    auto q = new int{7};
    f(q);
    int x = *q; // BAD: dereferences invalid pointer
}

```
##### Example

```cpp
void f()
{
    vector<int> v(10);
    int* p = v(5);
    v.pushback(99); // could rellocate v's elements
    int x = *p; // BAD: dereferences potentially invalid pointer
}

```
##### Enforcement

This rule is part ot the [lifetime profile](#Pro.lifetime)

* Flag a dereference of a pointer that points to an object that has gone out of scope
* Flag a dereference of a pointer that may have beed invalidated by assigning a `nullptr`
* Flag a dereference of a pointer that may have been invalidated by a `delete`
* Flag a dereference to a pointer to a container element that may have been invalidated by dereference

## <a name="SS-numbers"></a>Arithmetic

