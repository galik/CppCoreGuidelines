### <a name="Re-catch"></a>E.18: Minimize the use of explicit `try`/`catch`

##### Reason

 `try`/`catch` is verbose and non-trivial uses error-prone.
 `try`/`catch` can be a sign of unsystematic and/or low-level resource management or error handling.

##### Example, Bad

```cpp
void f(zstring s)
{
    Gadget* p;
    try {
        p = new Gadget(s);
        // ...
        delete p;
    }
    catch (Gadget_construction_failure) {
        delete p;
        throw;
    }
}

```
This code is messy.
There could be a leak from the naked pointer in the `try` block.
Not all exceptions are handled.
`deleting` an object that failed to construct is almost certainly a mistake.
Better:

```cpp
void f2(zstring s)
{
    Gadget g {s};
}

```
##### Alternatives

* proper resource handles and [RAII](I-13-Error%20handling-E.006.md#Re-raii)
* [`finally`](I-13-Error%20handling-E.019.md#Re-finally)

##### Enforcement

??? hard, needs a heuristic

