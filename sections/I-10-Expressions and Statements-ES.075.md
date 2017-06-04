### <a name="Res-do"></a>ES.75: Avoid `do`-statements

##### Reason

Readability, avoidance of errors.
The termination condition is at the end (where it can be overlooked) and the condition is not checked the first time through.

##### Example

```cpp
int x;
do {
    cin >> x;
    // ...
} while (x < 0);

```
##### Note

Yes, there are genuine examples where a `do`-statement is a clear statement of a solution, but also many bugs.

##### Enforcement

Flag `do`-statements.

