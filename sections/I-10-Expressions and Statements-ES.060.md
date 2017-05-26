### <a name="Res-new"></a>ES.60: Avoid `new` and `delete` outside resource management functions

##### Reason

Direct resource management in application code is error-prone and tedious.

##### Note

also known as "No naked `new`!"

##### Example, bad

```cpp
void f(int n)
{
    auto p = new X[n];   // n default constructed Xs
    // ...
    delete[] p;
}

```
There can be code in the `...` part that causes the `delete` never to happen.

**See also**: [R: Resource management](I-09-Resource management.md#S-resource).

##### Enforcement

Flag naked `new`s and naked `delete`s.

