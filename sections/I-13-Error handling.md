# <a name="S-errors"></a>E: Error handling

Error handling involves:

* Detecting an error
* Transmitting information about an error to some handler code
* Preserve the state of a program in a valid state
* Avoid resource leaks

It is not possible to recover from all errors. If recovery from an error is not possible, it is important to quickly "get out" in a well-defined way. A strategy for error handling must be simple, or it becomes a source of even worse errors.  Untested and rarely executed error-handling code is itself the source of many bugs.

The rules are designed to help avoid several kinds of errors:

* Type violations (e.g., misuse of `union`s and casts)
* Resource leaks (including memory leaks)
* Bounds errors
* Lifetime errors (e.g., accessing an object after is has been `delete`d)
* Complexity errors (logical errors make likely by overly complex expression of ideas)
* Interface errors (e.g., an unexpected value is passed through an interface)

Error-handling rule summary:

* [E.1: Develop an error-handling strategy early in a design](I-13-Error handling-E.001.md#Re-design)
* [E.2: Throw an exception to signal that a function can't perform its assigned task](I-13-Error handling-E.002.md#Re-throw)
* [E.3: Use exceptions for error handling only](I-13-Error handling-E.003.md#Re-errors)
* [E.4: Design your error-handling strategy around invariants](I-13-Error handling-E.004.md#Re-design-invariants)
* [E.5: Let a constructor establish an invariant, and throw if it cannot](I-13-Error handling-E.005.md#Re-invariant)
* [E.6: Use RAII to prevent leaks](I-13-Error handling-E.006.md#Re-raii)
* [E.7: State your preconditions](I-13-Error handling-E.007.md#Re-precondition)
* [E.8: State your postconditions](I-13-Error handling-E.008.md#Re-postcondition)

* [E.12: Use `noexcept` when exiting a function because of a `throw` is impossible or unacceptable](I-13-Error handling-E.012.md#Re-noexcept)
* [E.13: Never throw while being the direct owner of an object](I-13-Error handling-E.013.md#Re-never-throw)
* [E.14: Use purpose-designed user-defined types as exceptions (not built-in types)](I-13-Error handling-E.014.md#Re-exception-types)
* [E.15: Catch exceptions from a hierarchy by reference](I-13-Error handling-E.015.md#Re-exception-ref)
* [E.16: Destructors, deallocation, and `swap` must never fail](I-13-Error handling-E.016.md#Re-never-fail)
* [E.17: Don't try to catch every exception in every function](I-13-Error handling-E.017.md#Re-not-always)
* [E.18: Minimize the use of explicit `try`/`catch`](I-13-Error handling-E.018.md#Re-catch)
* [E.19: Use a `final_action` object to express cleanup if no suitable resource handle is available](I-13-Error handling-E.019.md#Re-finally)

* [E.25: If you can't throw exceptions, simulate RAII for resource management](I-13-Error handling-E.025.md#Re-no-throw-raii)
* [E.26: If you can't throw exceptions, consider failing fast](I-13-Error handling-E.026.md#Re-no-throw-crash)
* [E.27: If you can't throw exceptions, use error codes systematically](I-13-Error handling-E.027.md#Re-no-throw-codes)
* [E.28: Avoid error handling based on global state (e.g. `errno`)](I-13-Error handling-E.028.md#Re-no-throw)

* [E.30: Don't use exception specifications](I-13-Error handling-E.030.md#Re-specifications)
* [E.31: Properly order your `catch`-clauses](I-13-Error handling-E.031.md#Re_catch)

