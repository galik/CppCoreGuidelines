### <a name="Rnr-top"></a>NR.1: Don't: All declarations should be at the top of a function

##### Reason (not to follow this rule)

This rule is a legacy of old programming languages that didn't allow initialization of variables and constants after a statement.
This leads to longer programs and more errors caused by uninitialized and wrongly initialized variables.

##### Example, bad

```cpp
int use(int x)
{
    int i;
    char c;
    double d;

    // ... some stuff ...

    if (x < i) {
        // ...
        i = f(x, d);
    }
    if (i < x) {
        // ...
        i = g(x, c);
    }
    return i;
}

```
The larger the distance between the uninitialized variable and its use, the larger the chance of a bug.
Fortunately, compilers catch many "used before set" errors.
Unfortunately, compilers cannot catch all such errors and unfortunately, the bugs aren't always as simple to spot as in this small example.


##### Alternative

* [Always initialize an object](I-10-Expressions and Statements-ES.020.md#Res-always)
* [ES.21: Don't introduce a variable (or constant) before you need to use it](I-10-Expressions and Statements-ES.021.md#Res-introduce)

