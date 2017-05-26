### <a name="Rf-smart"></a>F.7: For general use, take `T*` or `T&` arguments rather than smart pointers

##### Reason

Passing a smart pointer transfers or shares ownership and should only be used when ownership semantics are intended (see [R.30](I-09-Resource management-R.030.md#Rr-smartptrparam)).
Passing by smart pointer restricts the use of a function to callers that use smart pointers.
Passing a shared smart pointer (e.g., `std::shared_ptr`) implies a run-time cost.

##### Example

```cpp
// accepts any int*
void f(int*);

// can only accept ints for which you want to transfer ownership
void g(unique_ptr<int>);

// can only accept ints for which you are willing to share ownership
void g(shared_ptr<int>);

// doesn't change ownership, but requires a particular ownership of the caller
void h(const unique_ptr<int>&);

// accepts any int
void h(int&);

```
##### Example, bad

```cpp
// callee
void f(shared_ptr<widget>& w)
{
    // ...
    use(*w); // only use of w -- the lifetime is not used at all
    // ...
};

```
See further in [R.30](I-09-Resource management-R.030.md#Rr-smartptrparam).

##### Note

We can catch dangling pointers statically, so we don't need to rely on resource management to avoid violations from dangling pointers.

**See also**: [when to prefer `T*` and when to prefer `T&`](I-05-Functions-F.060.md#Rf-ptr-ref).

**See also**: Discussion of [smart pointer use](I-09-Resource management.md#Rr-summary-smartptrs).

##### Enforcement

Flag a parameter of a smart pointer type (a type that overloads `operator->` or `operator*`) for which the ownership semantics are not used;
that is

* copyable but never copied/moved from or movable but never moved
* and that is never modified or passed along to another function that could do so.

