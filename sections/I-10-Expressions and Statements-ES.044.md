### <a name="Res-order-fct"></a>ES.44: Don't depend on order of evaluation of function arguments

##### Reason

Because that order is unspecified.

##### Note

C++17 tightens up the rules for the order of evaluation, but the order of evaluation of function arguments is still unspecified.

##### Example

    int i = 0;
    f(++i, ++i);

The call will most likely be `f(0, 1)` or `f(1, 0)`, but you don't know which.
Technically, the behavior is undefined.
In C++17, this code does not have undefined behavior, but it is still not specified which argument is evaluated first.

##### Example

Overloaded operators can lead to order of evaluation problems:

    f1()->m(f2());          // m(f1(), f2())
    cout << f1() << f2();   // operator<<(operator<<(cout, f1()), f2())

In C++17, these examples work as expected (left to right) and assignments are evaluated right to left (just as ='s binding is right-to-left)

    f1() = f2();    // undefined behavior in C++14; in C++17, f2() is evaluated before f1()

##### Enforcement

Can be detected by a good analyzer.

