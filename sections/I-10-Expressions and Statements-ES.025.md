### <a name="Res-const"></a>ES.25: Declare an object `const` or `constexpr` unless you want to modify its value later on

##### Reason

That way you can't change the value by mistake. That way may offer the compiler optimization opportunities.

##### Example

```cpp
void f(int n)
{
    const int bufmax = 2 * n + 2;  // good: we can't change bufmax by accident
    int xmax = n;                  // suspicious: is xmax intended to change?
    // ...
}

```
##### Enforcement

Look to see if a variable is actually mutated, and flag it if
not. Unfortunately, it may be impossible to detect when a non-`const` was not
*intended* to vary (vs when it merely did not vary).

