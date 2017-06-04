### <a name="Res-goto"></a>ES.76: Avoid `goto`

##### Reason

Readability, avoidance of errors. There are better control structures for humans; `goto` is for machine generated code.

##### Exception

Breaking out of a nested loop.
In that case, always jump forwards.

    for (int i = 0; i < imax; ++i)
        for (int j = 0; j < jmax; ++j) {
            if (a[i][j] > elem_max) goto finished;
            // ...
        }
    finished:
    // ...

##### Example, bad

There is a fair amount of use of the C goto-exit idiom:

    void f()
    {
        // ...
            goto exit;
        // ...
            goto exit;
        // ...
    exit:
        ... common cleanup code ...
    }

This is an ad-hoc simulation of destructors.
Declare your resources with handles with destructors that clean up.
If for some reason you cannot handle all cleanup with destructors for the variables used,
consider `gsl::finally()` as a cleaner and more reliable alternative to `goto exit`

##### Enforcement

* Flag `goto`. Better still flag all `goto`s that do not jump from a nested loop to the statement immediately after a nest of loops.

