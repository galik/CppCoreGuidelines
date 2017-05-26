### <a name="Res-del"></a>ES.61: Delete arrays using `delete[]` and non-arrays using `delete`

##### Reason

That's what the language requires and mistakes can lead to resource release errors and/or memory corruption.

##### Example, bad

```cpp
void f(int n)
{
    auto p = new X[n];   // n default constructed Xs
    // ...
    delete p;   // error: just delete the object p, rather than delete the array p[]
}

```
##### Note

This example not only violates the [no naked `new` rule](I-10-Expressions and Statements-ES.060.md#Res-new) as in the previous example, it has many more problems.

##### Enforcement

* if the `new` and the `delete` is in the same scope, mistakes can be flagged.
* if the `new` and the `delete` are in a constructor/destructor pair, mistakes can be flagged.

