### <a name="Res-default"></a>ES.79: Use `default` to handle common cases (only)

##### Reason

 Code clarity.
 Improved opportunities for error detection.

##### Example

    enum E { a, b, c , d };

    void f1(E x)
    {
        switch (x) {
        case a:
            do_something();
            break;
        case b:
            do_something_else();
            break;
        default:
            take_the_default_action();
            break;
        }
    }

Here it is clear that there is a default action and that cases `a` and `b` are special.

##### Example

But what if there is no default action and you mean to handle only specific cases?
In that case, have an empty default or else it is impossible to know if you meant to handle all cases:

    void f2(E x)
    {
        switch (x) {
        case a:
            do_something();
            break;
        case b:
            do_something_else();
            break;
        default:
            // do nothing for the rest of the cases
            break;
        }
    }

If you leave out the `default`, a maintainer and/or a compiler may reasonably assume that you intended to handle all cases:

    void f2(E x)
    {
        switch (x) {
        case a:
            do_something();
            break;
        case b:
        case c:
            do_something_else();
            break;
        }
    }

Did you forget case `d` or deliberately leave it out?
Forgetting a case typically happens when a case is added to an enumeration and the person doing so fails to add it to every
switch over the enumerators.

##### Enforcement

Flag `switch`-statements over an enumeration that don't handle all enumerators and do not have a `default`.
This may yield too many false positives in some code bases; if so, flag only `switch`es that handle most but not all cases
(that was the strategy of the very first C++ compiler).

