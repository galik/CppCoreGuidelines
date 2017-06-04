### <a name="Rr-scoped"></a>R.5: Prefer scoped objects, don't heap-allocate unnecessarily

##### Reason

A scoped object is a local object, a global object, or a member.
This implies that there is no separate allocation and deallocation cost in excess of that already used for the containing scope or object.
The members of a scoped object are themselves scoped and the scoped object's constructor and destructor manage the members' lifetimes.

##### Example

The following example is inefficient (because it has unnecessary allocation and deallocation), vulnerable to exception throws and returns in the `...` part (leading to leaks), and verbose:

    void f(int n)
    {
        auto p = new Gadget{n};
        // ...
        delete p;
    }

Instead, use a local variable:

    void f(int n)
    {
        Gadget g{n};
        // ...
    }

##### Enforcement

* (Moderate) Warn if an object is allocated and then deallocated on all paths within a function. Suggest it should be a local `auto` stack object instead.
* (Simple) Warn if a local `Unique_ptr` or `Shared_ptr` is not moved, copied, reassigned or `reset` before its lifetime ends.

