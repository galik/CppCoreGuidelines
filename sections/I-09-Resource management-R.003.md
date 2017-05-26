### <a name="Rr-ptr"></a>R.3: A raw pointer (a `T*`) is non-owning

##### Reason

There is nothing (in the C++ standard or in most code) to say otherwise and most raw pointers are non-owning.
We want owning pointers identified so that we can reliably and efficiently delete the objects pointed to by owning pointers.

##### Example

```cpp
void f()
{
    int* p1 = new int{7};           // bad: raw owning pointer
    auto p2 = make_unique<int>(7);  // OK: the int is owned by a unique pointer
    // ...
}

```
The `unique_ptr` protects against leaks by guaranteeing the deletion of its object (even in the presence of exceptions). The `T*` does not.

##### Example

```cpp
template<typename T>
class X {
    // ...
public:
    T* p;   // bad: it is unclear whether p is owning or not
    T* q;   // bad: it is unclear whether q is owning or not
};

```
We can fix that problem by making ownership explicit:

```cpp
template<typename T>
class X2 {
    // ...
public:
    owner<T*> p;  // OK: p is owning
    T* q;         // OK: q is not owning
};

```
##### Exception

A major class of exception is legacy code, especially code that must remain compilable as C or interface with C and C-style C++ through ABIs.
The fact that there are billions of lines of code that violate this rule against owning `T*`s cannot be ignored.
We'd love to see program transformation tools turning 20-year-old "legacy" code into shiny modern code,
we encourage the development, deployment and use of such tools,
we hope the guidelines will help the development of such tools,
and we even contributed (and contribute) to the research and development in this area.
However, it will take time: "legacy code" is generated faster than we can renovate old code, and so it will be for a few years.

This code cannot all be rewritten (ever assuming good code transformation software), especially not soon.
This problem cannot be solved (at scale) by transforming all owning pointers to `unique_ptr`s and `shared_ptr`s,
partly because we need/use owning "raw pointers" as well as simple pointers in the implementation of our fundamental resource handles.
For example, common `vector` implementations have one owning pointer and two non-owning pointers.
Many ABIs (and essentially all interfaces to C code) use `T*`s, some of them owning.
Some interfaces cannot be simply annotated with `owner` because they need to remain compilable as C
(although this would be a rare good use for a macro, that expands to `owner` in C++ mode only).

##### Note

`owner<T*>` has no default semantics beyond `T*`. It can be used without changing any code using it and without affecting ABIs.
It is simply a indicator to programmers and analysis tools.
For example, if an `owner<T*>` is a member of a class, that class better have a destructor that `delete`s it.

##### Example, bad

Returning a (raw) pointer imposes a life-time management uncertainty on the caller; that is, who deletes the pointed-to object?

```cpp
Gadget* make_gadget(int n)
{
    auto p = new Gadget{n};
    // ...
    return p;
}

void caller(int n)
{
    auto p = make_gadget(n);   // remember to delete p
    // ...
    delete p;
}

```
In addition to suffering from the problem from [leak](#???), this adds a spurious allocation and deallocation operation, and is needlessly verbose. If Gadget is cheap to move out of a function (i.e., is small or has an efficient move operation), just return it "by value" (see ["out" return values](I-05-Functions-F.020.md#Rf-out)):

```cpp
Gadget make_gadget(int n)
{
    Gadget g{n};
    // ...
    return g;
}

```
##### Note

This rule applies to factory functions.

##### Note

If pointer semantics are required (e.g., because the return type needs to refer to a base class of a class hierarchy (an interface)), return a "smart pointer."

##### Enforcement

* (Simple) Warn on `delete` of a raw pointer that is not an `owner<T>`.
* (Moderate) Warn on failure to either `reset` or explicitly `delete` an `owner<T>` pointer on every code path.
* (Simple) Warn if the return value of `new` is assigned to a raw pointer.
* (Simple) Warn if a function returns an object that was allocated within the function but has a move constructor.
  Suggest considering returning it by value instead.

