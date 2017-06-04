### <a name="Ru-naked"></a>C.181: Avoid "naked" `union`s

##### Reason

A *naked union* is a union without an associated indicator which member (if any) it holds,
so that the programmer has to keep track.
Naked unions are a source of type errors.

##### Example, bad

    union Value {
        int x;
        double d;
    };

    Value v;
    v.d = 987.654;  // v holds a double

So far, so good, but we can easily misuse the `union`:

    cout << v.x << '\n';    // BAD, undefined behavior: v holds a double, but we read it as an int

Note that the type error happened without any explicit cast.
When we tested that program the last value printed was `1683627180` which it the integer value for the bit pattern for `987.654`.
What we have here is an "invisible" type error that happens to give a result that could easily look innocent.

And, talking about "invisible", this code produced no output:

    v.x = 123;
    cout << v.d << '\n';    // BAD: undefined behavior

##### Alternative

Wrap a `union` in a class together with a type field.

The soon-to-be-standard `variant` type (to be found in `<variant>`) does that for you:

    variant<int, double> v;
    v = 123;        // v holds an int
    int x = get<int>(v);
    v = 123.456;    // v holds a double
    w = get<double>(v);

##### Enforcement

???

