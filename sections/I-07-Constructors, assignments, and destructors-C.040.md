### <a name="Rc-ctor"></a>C.40: Define a constructor if a class has an invariant

##### Reason

That's what constructors are for.

##### Example

```cpp
class Date {  // a Date represents a valid date
              // in the January 1, 1900 to December 31, 2100 range
    Date(int dd, int mm, int yy)
        :d{dd}, m{mm}, y{yy}
    {
        if (!is_valid(d, m, y)) throw Bad_date{};  // enforce invariant
    }
    // ...
private:
    int d, m, y;
};

```
It is often a good idea to express the invariant as an `Ensures` on the constructor.

##### Note

A constructor can be used for convenience even if a class does not have an invariant. For example:

```cpp
struct Rec {
    string s;
    int i {0};
    Rec(const string& ss) : s{ss} {}
    Rec(int ii) :i{ii} {}
};

Rec r1 {7};
Rec r2 {"Foo bar"};

```
##### Note

The C++11 initializer list rule eliminates the need for many constructors. For example:

```cpp
struct Rec2{
    string s;
    int i;
    Rec2(const string& ss, int ii = 0) :s{ss}, i{ii} {}   // redundant
};

Rec2 r1 {"Foo", 7};
Rec2 r2 {"Bar"};

```
The `Rec2` constructor is redundant.
Also, the default for `int` would be better done as a [member initializer](I-07-Constructors%2C%20assignments%2C%20and%20destructors-C.048.md#Rc-in-class-initializer).

**See also**: [construct valid object](I-07-Constructors%2C%20assignments%2C%20and%20destructors-C.041.md#Rc-complete) and [constructor throws](I-07-Constructors%2C%20assignments%2C%20and%20destructors-C.042.md#Rc-throw).

##### Enforcement

* Flag classes with user-defined copy operations but no constructor (a user-defined copy is a good indicator that the class has an invariant)

