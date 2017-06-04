### <a name="Re-no-throw-raii"></a>E.25: If you can't throw exceptions, simulate RAII for resource management

##### Reason

Even without exceptions, [RAII](I-13-Error%20handling-E.006.md#Re-raii) is usually the best and most systematic way of dealing with resources.

##### Note

Error handling using exceptions is the only complete and systematic way of handling non-local errors in C++.
In particular, non-intrusively signaling failure to construct an object requires an exception.
Signaling errors in a way that cannot be ignored requires exceptions.
If you can't use exceptions, simulate their use as best you can.

A lot of fear of exceptions is misguided.
When used for exceptional circumstances in code that is not littered with pointers and complicated control structures,
exception handling is almost always affordable (in time and space) and almost always leads to better code.
This, of course, assumes a good implementation of the exception handling mechanisms, which is not available on all systems.
There are also cases where the problems above do not apply, but exceptions cannot be used for other reasons.
Some hard real-time systems are an example: An operation has to be completed within a fixed time with an error or a correct answer.
In the absence of appropriate time estimation tools, this is hard to guarantee for exceptions.
Such systems (e.g. flight control software) typically also ban the use of dynamic (heap) memory.

So, the primary guideline for error handling is "use exceptions and [RAII](I-13-Error%20handling-E.006.md#Re-raii)."
This section deals with the cases where you either do not have an efficient implementation of exceptions,
or have such a rat's nest of old-style code
(e.g., lots of pointers, ill-defined ownership, and lots of unsystematic error handling based on tests of error codes)
that it is infeasible to introduce simple and systematic exception handling.

Before condemning exceptions or complaining too much about their cost, consider examples of the use of [error codes](I-13-Error%20handling-E.027.md#Re-no-throw-codes).
Consider the cost and complexity of the use of error codes.
If performance is your worry, measure.

##### Example

Assume you wanted to write

    void func(zstring arg)
    {
        Gadget g {arg};
        // ...
    }

If the `gadget` isn't correctly constructed, `func` exits with an exception.
If we cannot throw an exception, we can simulate this RAII style of resource handling by adding a `valid()` member function to `Gadget`:

    error_indicator func(zstring arg)
    {
        Gadget g {arg};
        if (!g.valid()) return gadget_construction_error;
        // ...
        return 0;   // zero indicates "good"
    }

The problem is of course that the caller now has to remember to test the return value.

**See also**: [Discussion](#Sd-???).

##### Enforcement

Possible (only) for specific versions of this idea: e.g., test for systematic test of `valid()` after resource handle construction

