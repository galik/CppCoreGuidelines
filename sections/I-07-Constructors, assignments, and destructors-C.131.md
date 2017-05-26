### <a name="Rh-get"></a>C.131: Avoid trivial getters and setters

##### Reason

A trivial getter or setter adds no semantic value; the data item could just as well be `public`.

##### Example

```cpp
class Point {   // Bad: verbose
    int x;
    int y;
public:
    Point(int xx, int yy) : x{xx}, y{yy} { }
    int get_x() const { return x; }
    void set_x(int xx) { x = xx; }
    int get_y() const { return y; }
    void set_y(int yy) { y = yy; }
    // no behavioral member functions
};

```
Consider making such a class a `struct` -- that is, a behaviorless bunch of variables, all public data and no member functions.

```cpp
struct Point {
    int x {0};
    int y {0};
};

```
Note that we can put default initializers on member variables: [C.49: Prefer initialization to assignment in constructors](I-07-Constructors%2C%20assignments%2C%20and%20destructors-C.049.md#Rc-initialize).

##### Note

The key to this rule is whether the semantics of the getter/setter are trivial. While it is not a complete definition of "trivial", consider whether there would be any difference beyond syntax if the getter/setter was a public data member instead. Examples of non-trivial semantics would be: maintaining a class invariant or converting between an internal type and an interface type.

##### Enforcement

Flag multiple `get` and `set` member functions that simply access a member without additional semantics.

