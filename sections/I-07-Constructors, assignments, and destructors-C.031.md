### <a name="Rc-dtor-release"></a>C.31: All resources acquired by a class must be released by the class's destructor

##### Reason

Prevention of resource leaks, especially in error cases.

##### Note

For resources represented as classes with a complete set of default operations, this happens automatically.

##### Example

    class X {
        ifstream f;   // may own a file
        // ... no default operations defined or =deleted ...
    };

`X`'s `ifstream` implicitly closes any file it may have open upon destruction of its `X`.

##### Example, bad

    class X2 {     // bad
        FILE* f;   // may own a file
        // ... no default operations defined or =deleted ...
    };

`X2` may leak a file handle.

##### Note

What about a sockets that won't close? A destructor, close, or cleanup operation [should never fail](I-07-Constructors%2C%20assignments%2C%20and%20destructors-C.036.md#Rc-dtor-fail).
If it does nevertheless, we have a problem that has no really good solution.
For starters, the writer of a destructor does not know why the destructor is called and cannot "refuse to act" by throwing an exception.
See [discussion](I-28-Discussion-Discussion.md#Sd-never-fail).
To make the problem worse, many "close/release" operations are not retryable.
Many have tried to solve this problem, but no general solution is known.
If at all possible, consider failure to close/cleanup a fundamental design error and terminate.

##### Note

A class can hold pointers and references to objects that it does not own.
Obviously, such objects should not be `delete`d by the class's destructor.
For example:

    Preprocessor pp { /* ... */ };
    Parser p { pp, /* ... */ };
    Type_checker tc { p, /* ... */ };

Here `p` refers to `pp` but does not own it.

##### Enforcement

* (Simple) If a class has pointer or reference member variables that are owners
  (e.g., deemed owners by using `gsl::owner`), then they should be referenced in its destructor.
* (Hard) Determine if pointer or reference member variables are owners when there is no explicit statement of ownership
  (e.g., look into the constructors).

