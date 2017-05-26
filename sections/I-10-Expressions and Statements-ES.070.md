### <a name="Res-switch-if"></a>ES.70: Prefer a `switch`-statement to an `if`-statement when there is a choice

##### Reason

* Readability.
* Efficiency: A `switch` compares against constants and is usually better optimized than a series of tests in an `if`-`then`-`else` chain.
* A `switch` enables some heuristic consistency checking. For example, have all values of an `enum` been covered? If not, is there a `default`?

##### Example

```cpp
void use(int n)
{
    switch (n) {   // good
    case 0:   // ...
    case 7:   // ...
    }
}

```
rather than:

```cpp
void use2(int n)
{
    if (n == 0)   // bad: if-then-else chain comparing against a set of constants
        // ...
    else if (n == 7)
        // ...
}

```
##### Enforcement

Flag `if`-`then`-`else` chains that check against constants (only).

