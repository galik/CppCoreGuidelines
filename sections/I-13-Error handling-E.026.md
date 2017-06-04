### <a name="Re-no-throw-crash"></a>E.26: If you can't throw exceptions, consider failing fast

##### Reason

If you can't do a good job at recovering, at least you can get out before too much consequential damage is done.

See also [Simulating RAII](I-13-Error%20handling-E.025.md#Re-no-throw-raii).

##### Note

If you cannot be systematic about error handling, consider "crashing" as a response to any error that cannot be handled locally.
That is, if you cannot recover from an error in the context of the function that detected it, call `abort()`, `quick_exit()`,
or a similar function that will trigger some sort of system restart.

In systems where you have lots of processes and/or lots of computers, you need to expect and handle fatal crashes anyway,
say from hardware failures.
In such cases, "crashing" is simply leaving error handling to the next level of the system.

##### Example

    void f(int n)
    {
        // ...
        p = static_cast<X*>(malloc(n, X));
        if (p == nullptr) abort();     // abort if memory is exhausted
        // ...
    }

Most programs cannot handle memory exhaustion gracefully anyway. This is roughly equivalent to

    void f(int n)
    {
        // ...
        p = new X[n];    // throw if memory is exhausted (by default, terminate)
        // ...
    }

Typically, it is a good idea to log the reason for the "crash" before exiting.

##### Enforcement

Awkward

