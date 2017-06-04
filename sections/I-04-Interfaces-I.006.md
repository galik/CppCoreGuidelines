### <a name="Ri-expects"></a>I.6: Prefer `Expects()` for expressing preconditions

##### Reason

To make it clear that the condition is a precondition and to enable tool use.

##### Example

```cpp
int area(int height, int width)
{
    Expects(height > 0 && width > 0);            // good
    if (height <= 0 || width <= 0) my_error();   // obscure
    // ...
}

```
##### Note

Preconditions can be stated in many ways, including comments, `if`-statements, and `assert()`.
This can make them hard to distinguish from ordinary code, hard to update, hard to manipulate by tools, and may have the wrong semantics (do you always want to abort in debug mode and check nothing in productions runs?).

##### Note

Preconditions should be part of the interface rather than part of the implementation,
but we don't yet have the language facilities to do that.
Once language support becomes available (e.g., see the [contract proposal](http://www.open-std.org/jtc1/sc22/wg21/docs/papers/2016/p0380r1.pdf)) we will adopt the standard version of preconditions, postconditions, and assertions.

##### Note

`Expects()` can also be used to check a condition in the middle of an algorithm.

##### Note

No, using `unsigned` is not a good way to sidestep the problem of [ensuring that a value is nonnegative](I-10-Expressions%20and%20Statements-ES.106.md#Res-nonnegative).

##### Enforcement

(Not enforceable) Finding the variety of ways preconditions can be asserted is not feasible. Warning about those that can be easily identified (`assert()`) has questionable value in the absence of a language facility.

