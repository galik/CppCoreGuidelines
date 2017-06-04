### <a name="Rf-inout"></a>F.17: For "in-out" parameters, pass by reference to non-`const`

##### Reason

This makes it clear to callers that the object is assumed to be modified.

##### Example

    void update(Record& r);  // assume that update writes to r

##### Note

A `T&` argument can pass information into a function as well as well as out of it.
Thus `T&` could be an in-out-parameter. That can in itself be a problem and a source of errors:

    void f(string& s)
    {
        s = "New York";  // non-obvious error
    }

    void g()
    {
        string buffer = ".................................";
        f(buffer);
        // ...
    }

Here, the writer of `g()` is supplying a buffer for `f()` to fill, but `f()` simply replaces it (at a somewhat higher cost than a simple copy of the characters).
A bad logic error can happen if the writer of `g()` incorrectly assumes the size of the `buffer`.

##### Enforcement

* (Moderate) ((Foundation)) Warn about functions regarding reference to non-`const` parameters that do *not* write to them.
* (Simple) ((Foundation)) Warn when a non-`const` parameter being passed by reference is `move`d.

