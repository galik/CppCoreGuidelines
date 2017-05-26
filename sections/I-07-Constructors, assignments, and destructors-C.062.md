### <a name="Rc-copy-self"></a>C.62: Make copy assignment safe for self-assignment

##### Reason

If `x = x` changes the value of `x`, people will be surprised and bad errors will occur (often including leaks).

##### Example

The standard-library containers handle self-assignment elegantly and efficiently:

```cpp
std::vector<int> v = {3, 1, 4, 1, 5, 9};
v = v;
// the value of v is still {3, 1, 4, 1, 5, 9}

```
##### Note

The default assignment generated from members that handle self-assignment correctly handles self-assignment.

```cpp
struct Bar {
    vector<pair<int, int>> v;
    map<string, int> m;
    string s;
};

Bar b;
// ...
b = b;   // correct and efficient

```
##### Note

You can handle self-assignment by explicitly testing for self-assignment, but often it is faster and more elegant to cope without such a test (e.g., [using `swap`](I-07-Constructors%2C%20assignments%2C%20and%20destructors-C.083.md#Rc-swap)).

```cpp
class Foo {
    string s;
    int i;
public:
    Foo& operator=(const Foo& a);
    // ...
};

Foo& Foo::operator=(const Foo& a)   // OK, but there is a cost
{
    if (this == &a) return *this;
    s = a.s;
    i = a.i;
    return *this;
}

```
This is obviously safe and apparently efficient.
However, what if we do one self-assignment per million assignments?
That's about a million redundant tests (but since the answer is essentially always the same, the computer's branch predictor will guess right essentially every time).
Consider:

```cpp
Foo& Foo::operator=(const Foo& a)   // simpler, and probably much better
{
    s = a.s;
    i = a.i;
    return *this;
}

```
`std::string` is safe for self-assignment and so are `int`. All the cost is carried by the (rare) case of self-assignment.

##### Enforcement

(Simple) Assignment operators should not contain the pattern `if (this == &a) return *this;` ???

