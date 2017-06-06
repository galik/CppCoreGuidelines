### <a name="Rf-noexcept"></a>F.6: If your function may not throw, declare it `noexcept`

##### Reason

If an exception is not supposed to be thrown, the program cannot be assumed to cope with the error and should be terminated as soon as possible. Declaring a function `noexcept` helps optimizers by reducing the number of alternative execution paths. It also speeds up the exit after failure.

##### Example

Put `noexcept` on every function written completely in C or in any other language without exceptions.
The C++ standard library does that implicitly for all functions in the C standard library.

##### Note

`constexpr` functions can throw when evaluated at run time, so you may need `noexcept` for some of those.

##### Example

You can use `noexcept` even on functions that can throw:

```cpp
vector<string> collect(istream& is) noexcept
{
    vector<string> res;
    for (string s; is >> s;)
        res.push_back(s);
    return res;
}

```
If `collect()` runs out of memory, the program crashes.
Unless the program is crafted to survive memory exhaustion, that may be just the right thing to do;
`terminate()` may generate suitable error log information (but after memory runs out it is hard to do anything clever).

##### Note

You must be aware of the execution environment that your code is running when
deciding whether to tag a function `noexcept`, especially because of the issue
of throwing and allocation.  Code that is intended to be perfectly general (like
the standard library and other utility code of that sort) needs to support
environments where a `bad_alloc` exception may be handled meaningfully.
However, most programs and execution environments cannot meaningfully
handle a failure to allocate, and aborting the program is the cleanest and
simplest response to an allocation failure in those cases.  If you know that
your application code cannot respond to an allocation failure, it may be
appropriate to add `noexcept` even on functions that allocate.

Put another way: In most programs, most functions can throw (e.g., because they
use `new`, call functions that do, or use library functions that reports failure
by throwing), so don't just sprinkle `noexcept` all over the place without
considering whether the possible exceptions can be handled.

`noexcept` is most useful (and most clearly correct) for frequently used,
low-level functions.

##### Note

Destructors, `swap` functions, move operations, and default constructors should never throw.

##### Enforcement

* Flag functions that are not `noexcept`, yet cannot throw.
* Flag throwing `swap`, `move`, destructors, and default constructors.

