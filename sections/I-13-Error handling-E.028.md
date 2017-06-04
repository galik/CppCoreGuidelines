### <a name="Re-no-throw"></a>E.28: Avoid error handling based on global state (e.g. `errno`)

##### Reason

Global state is hard to manage and it is easy to forget to check it.
When did you last test the return value of `printf()`?

See also [Simulating RAII](I-13-Error%20handling-E.025.md#Re-no-throw-raii).

##### Example, bad

    ???

##### Note

C-style error handling is based on the global variable `errno`, so it is essentially impossible to avoid this style completely.

##### Enforcement

Awkward.


