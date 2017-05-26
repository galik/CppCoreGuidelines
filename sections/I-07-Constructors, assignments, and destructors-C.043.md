### <a name="Rc-default0"></a>C.43: Ensure that a value type class has a default constructor

##### Reason

Many language and library facilities rely on default constructors to initialize their elements, e.g. `T a[10]` and `std::vector<T> v(10)`.
A default constructor often simplifies the task of defining a suitable [moved-from state](#???).

##### Note

We have not (yet) formally defined [value type](I-06-Classes and Class Hierarchies-C.009.md#SS-concrete), but think of it as a class that behaves much as an `int`:
it can be copied using `=` and usually compared using `==`.
It is closely related to the notion of Regular type from [EoP](http://elementsofprogramming.com/) and [the Palo Alto TR](http://www.open-std.org/jtc1/sc22/wg21/docs/papers/2012/n3351.pdf).

##### Example

```cpp
class Date { // BAD: no default constructor
public:
    Date(int dd, int mm, int yyyy);
    // ...
};

vector<Date> vd1(1000);   // default Date needed here
vector<Date> vd2(1000, Date{Month::October, 7, 1885});   // alternative

```
The default constructor is only auto-generated if there is no user-declared constructor, hence it's impossible to initialize the vector `vd1` in the example above.
The absence of a default value can cause surprises for users and complicate its use, so if one can be reasonably defined, it should be.

`Date` is chosen to encourage thought:
There is no "natural" default date (the big bang is too far back in time to be useful for most people), so this example is non-trivial.
`{0, 0, 0}` is not a valid date in most calendar systems, so choosing that would be introducing something like floating-point's `NaN`.
However, most realistic `Date` classes have a "first date" (e.g. January 1, 1970 is popular), so making that the default is usually trivial.

```cpp
class Date {
public:
    Date(int dd, int mm, int yyyy);
    Date() = default; // [See also](I-07-Constructors, assignments, and destructors-C.045.md#Rc-default)
    // ...
private:
    int dd = 1;
    int mm = 1;
    int yyyy = 1970;
    // ...
};

vector<Date> vd1(1000);

```
##### Note

A class with members that all have default constructors implicitly gets a default constructor:

```cpp
struct X {
    string s;
    vector<int> v;
};

X x; // means X{{}, {}}; that is the empty string and the empty vector

```
Beware that built-in types are not properly default constructed:

```cpp
struct X {
    string s;
    int i;
};

void f()
{
    X x;    // x.s is initialized to the empty string; x.i is uninitialized

    cout << x.s << ' ' << x.i << '\n';
    ++x.i;
}

```
Statically allocated objects of built-in types are by default initialized to `0`, but local built-in variables are not.
Beware that your compiler may default initialize local built-in variables, whereas an optimized build will not.
Thus, code like the example above may appear to work, but it relies on undefined behavior.
Assuming that you want initialization, an explicit default initialization can help:

```cpp
struct X {
    string s;
    int i {};   // default initialize (to 0)
};

```
##### Example

There are classes that simply don't have a reasonable default.

A class designed to be useful only as a base does not need a default constructor because it cannot be constructed by itself:

```cpp
struct Shape {  // pure interface: all members are pure virtual functions
        void draw() = 0;
        void rotate(int) = 0;
        // ...
};

```
A class that must acquire a resource during construction:

```cpp
lock_guard g {mx};  // guard the mutex mx
lock_guard g2;      // error: guarding nothing

```
##### Note

A class that has a "special state" that must be handled separately from other states by member functions or users causes extra work
(and most likely more errors). For example

```cpp
ofstream out {"Foobar"};
// ...
out << log(time, transaction);

```
If `Foobar` couldn't be opened for writing and `out` wasn't set to throw exceptions upon errors, the output operations become no-ops.
The implementation must take care of that case, and users must remember to test for success.

Pointers, even smart pointers, that can point to nothing (null pointers) are an example of this.
Having a default constructor is not a panacea; ideally it defaults to a meaningful state such as `std::string`s `""` and `std::vector`s `{}`.

##### Enforcement

* Flag classes that are copyable by `=` or comparable with `==` without a default constructor

