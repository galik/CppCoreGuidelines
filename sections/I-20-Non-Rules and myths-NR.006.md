### <a name="Rnr-goto-exit"></a>NR.6: Don't: Place all cleanup actions at the end of a function and `goto exit`

##### Reason (not to follow this rule)

`goto` is error-prone.
This technique is a pre-exception technique for RAII-like resource and error handling.

##### Example, bad

    void do_something(int n)
    {
        if (n < 100) goto exit;
        // ...
        int* p = (int*) malloc(n);
        // ...
        if (some_ error) goto_exit;
        // ...
    exit:
        free(p);
    }

and spot the bug.

##### Alternative

* Use exceptions and [RAII](I-13-Error%20handling-E.006.md#Re-raii)
* for non-RAII resources, use [`finally`](I-13-Error%20handling-E.019.md#Re-finally).

