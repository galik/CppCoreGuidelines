### <a name="Res-underflow"></a>ES.104: Don't underflow

##### Reason

Decrementing a value beyond a minimum value can lead to memory corruption and undefined behavior.

##### Example, bad

    int a[10];
    a[-2] = 7;   // bad

    int n = 101;
    while (n--)
        a[n - 1] = 9;   // bad (twice)

##### Exception

Use unsigned types if you really want modulo arithmetic.

##### Enforcement

???

