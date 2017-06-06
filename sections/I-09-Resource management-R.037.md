### <a name="Rr-smartptrget"></a>R.37: Do not pass a pointer or reference obtained from an aliased smart pointer

##### Reason

Violating this rule is the number one cause of losing reference counts and finding yourself with a dangling pointer.
Functions should prefer to pass raw pointers and references down call chains.
At the top of the call tree where you obtain the raw pointer or reference from a smart pointer that keeps the object alive.
You need to be sure that the smart pointer cannot inadvertently be reset or reassigned from within the call tree below.

##### Note

To do this, sometimes you need to take a local copy of a smart pointer, which firmly keeps the object alive for the duration of the function and the call tree.

##### Example

Consider this code:

```cpp
// global (static or heap), or aliased local ...
shared_ptr<widget> g_p = ...;

void f(widget& w)
{
    g();
    use(w);  // A
}

void g()
{
    g_p = ...; // oops, if this was the last shared_ptr to that widget, destroys the widget
}

```
The following should not pass code review:

```cpp
void my_code()
{
    // BAD: passing pointer or reference obtained from a nonlocal smart pointer
    //      that could be inadvertently reset somewhere inside f or it callees
    f(*g_p);

    // BAD: same reason, just passing it as a "this" pointer
     g_p->func();
}

```
The fix is simple -- take a local copy of the pointer to "keep a ref count" for your call tree:

```cpp
void my_code()
{
    // cheap: 1 increment covers this entire function and all the call trees below us
    auto pin = g_p;

    // GOOD: passing pointer or reference obtained from a local unaliased smart pointer
    f(*pin);

    // GOOD: same reason
    pin->func();
}

```
##### Enforcement

* (Simple) Warn if a pointer or reference obtained from a smart pointer variable (`Unique_ptr` or `Shared_ptr`) that is nonlocal, or that is local but potentially aliased, is used in a function call. If the smart pointer is a `Shared_ptr` then suggest taking a local copy of the smart pointer and obtain a pointer or reference from that instead.

