### <a name="Ri-except"></a>I.10: Use exceptions to signal a failure to perform a required task

##### Reason

It should not be possible to ignore an error because that could leave the system or a computation in an undefined (or unexpected) state.
This is a major source of errors.

##### Example

    int printf(const char* ...);    // bad: return negative number if output fails

    template <class F, class ...Args>
    // good: throw system_error if unable to start the new thread
    explicit thread(F&& f, Args&&... args);

##### Note

What is an error?

An error means that the function cannot achieve its advertised purpose (including establishing postconditions).
Calling code that ignores an error could lead to wrong results or undefined systems state.
For example, not being able to connect to a remote server is not by itself an error:
the server can refuse a connection for all kinds of reasons, so the natural thing is to return a result that the caller should always check.
However, if failing to make a connection is considered an error, then a failure should throw an exception.

##### Exception

Many traditional interface functions (e.g., UNIX signal handlers) use error codes (e.g., `errno`) to report what are really status codes, rather than errors. You don't have a good alternative to using such, so calling these does not violate the rule.

##### Alternative

If you can't use exceptions (e.g. because your code is full of old-style raw-pointer use or because there are hard-real-time constraints), consider using a style that returns a pair of values:

    int val;
    int error_code;
    tie(val, error_code) = do_something();
    if (error_code == 0) {
        // ... handle the error or exit ...
    }
    // ... use val ...

This style unfortunately leads to uninitialized variables.
A facility [structured bindings](http://www.open-std.org/jtc1/sc22/wg21/docs/papers/2016/p0144r1.pdf) to deal with that will become available in C++17.

    auto [val, error_code] = do_something();
    if (error_code == 0) {
        // ... handle the error or exit ...
    }
    // ... use val ...

##### Note

We don't consider "performance" a valid reason not to use exceptions.

* Often, explicit error checking and handling consume as much time and space as exception handling.
* Often, cleaner code yields better performance with exceptions (simplifying the tracing of paths through the program and their optimization).
* A good rule for performance critical code is to move checking outside the critical part of the code ([checking](#Rper-checking)).
* In the longer term, more regular code gets better optimized.
* Always carefully [measure](I-11-Performance-Per.006.md#Rper-measure) before making performance claims.

**See also**: [I.5](I-04-Interfaces-I.005.md#Ri-pre) and [I.7](I-04-Interfaces-I.007.md#Ri-post) for reporting precondition and postcondition violations.

##### Enforcement

* (Not enforceable) This is a philosophical guideline that is infeasible to check directly.
* Look for `errno`.

