### <a name="Res-arr2"></a>ES.62: Don't compare pointers into different arrays

##### Reason

The result of doing so is undefined.

##### Example, bad

```cpp
void f(int n)
{
    int a1[7];
    int a2[9];
    if (&a1[5] < &a2[7]) {}       // bad: undefined
    if (0 < &a1[5] - &a2[7]) {}   // bad: undefined
}

```
##### Note

This example has many more problems.

##### Enforcement

???

