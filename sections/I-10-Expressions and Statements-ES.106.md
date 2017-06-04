### <a name="Res-nonnegative"></a>ES.106: Don't try to avoid negative values by using `unsigned`

##### Reason

Choosing `unsigned` implies many changes to the usual behavior of integers, including modulo arithmetic,
can suppress warnings related to overflow,
and opens the door for errors related to signed/unsigned mixes.
Using `unsigned` doesn't actually eliminate the possibility of negative values.

##### Example

    unsigned int u1 = -2;   // OK: the value of u1 is 4294967294
    int i1 = -2;
    unsigned int u2 = i1;   // OK: the value of u2 is 4294967294
    int i2 = u2;            // OK: the value of i2 is -2

These problems with such (perfectly legal) constructs are hard to spot in real code and are the source of many real-world errors.
Consider:

    unsigned area(unsigned height, unsigned width) { return height*width; } // [see also](I-04-Interfaces-I.006.md#Ri-expects)
    // ...
    int height;
    cin >> height;
    auto a = area(height, 2);   // if the input is -2 a becomes 4294967292

Remember that `-1` when assigned to an `unsigned int` becomes the largest `unsigned int`.
Also, since unsigned arithmetic is modulo arithmetic the multiplication didn't overflow, it wrapped around.

##### Example

    unsigned max = 100000;    // "accidental typo", I mean to say 10'000
    unsigned short x = 100;
    while (x < max) x += 100; // infinite loop

Had `x` been a signed `short`, we could have warned about the undefined behavior upon overflow.

##### Alternatives

* use signed integers and check for `x >= 0`
* use a positive integer type
* use an integer subrange type
* `Assert(-1 < x)`

For example

    struct Positive {
        int val;
        Positive(int x) :val{x} { Assert(0 < x); }
        operator int() { return val; }
    };

    int f(Positive arg) {return arg };

    int r1 = f(2);
    int r2 = f(-2);  // throws

##### Note

???

##### Enforcement

Hard: there is a lot of code using `unsigned` and we don't offer a practical positive number type.


