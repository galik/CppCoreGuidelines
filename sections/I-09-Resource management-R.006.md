### <a name="Rr-global"></a>R.6: Avoid non-`const` global variables

##### Reason

Global variables can be accessed from everywhere so they can introduce surprising dependencies between apparently unrelated objects.
They are a notable source of errors.

**Warning**: The initialization of global objects is not totally ordered.
If you use a global object initialize it with a constant.
Note that it is possible to get undefined initialization order even for `const` objects.

##### Exception

A global object is often better than a singleton.

##### Exception

An immutable (`const`) global does not introduce the problems we try to avoid by banning global objects.

##### Enforcement

(??? NM: Obviously we can warn about non-`const` statics ... do we want to?)

## <a name="SS-alloc"></a>R.alloc: Allocation and deallocation

