### <a name="Ri-ensures"></a>I.8: Prefer `Ensures()` for expressing postconditions

##### Reason

To make it clear that the condition is a postcondition and to enable tool use.

##### Example

    void f()
    {
        char buffer[MAX];
        // ...
        memset(buffer, 0, MAX);
        Ensures(buffer[0] == 0);
    }

##### Note

Postconditions can be stated in many ways, including comments, `if`-statements, and `assert()`.
This can make them hard to distinguish from ordinary code, hard to update, hard to manipulate by tools, and may have the wrong semantics.

**Alternative**: Postconditions of the form "this resource must be released" are best expressed by [RAII](I-09-Resource%20management-R.001.md#Rr-raii).

##### Note

Ideally, that `Ensures` should be part of the interface, but that's not easily done.
For now, we place it in the definition (function body).
Once language support becomes available (e.g., see the [contract proposal](http://www.open-std.org/jtc1/sc22/wg21/docs/papers/2016/p0380r1.pdf)) we will adopt the standard version of preconditions, postconditions, and assertions.

##### Enforcement

(Not enforceable) Finding the variety of ways postconditions can be asserted is not feasible. Warning about those that can be easily identified (`assert()`) has questionable value in the absence of a language facility.

