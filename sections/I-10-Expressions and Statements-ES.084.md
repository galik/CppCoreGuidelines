### <a name="Res-noname"></a>ES.84: Don't (try to) declare a local variable with no name

##### Reason

There is no such thing.
What looks to a human like a variable without a name is to the compiler a statement consisting of a temporary that immediately goes out of scope.
To avoid unpleasant surprises.

##### Example, bad

```cpp
void f()
{
    lock<mutex>{mx};   // Bad
    // ...
}

```
This declares an unnamed `lock` object that immediately goes out of scope at the point of the semicolon.
This is not an uncommon mistake.
In particular, this particular example can lead to hard-to find race conditions.
There are exceedingly clever used of this "idiom", but they are far rarer than the mistakes.

##### Note

Unnamed function arguments are fine.

##### Enforcement

Flag statements that are just a temporary

