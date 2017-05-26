### <a name="Res-construct"></a>ES.64: Use the `T{e}`notation for construction

##### Reason

The `T{e}` construction syntax makes it explicit that construction is desired.
The `T{e}` construction syntax doesn't allow narrowing.
`T{e}` is the only safe and general expression for constructing a value of type `T` from an expression `e`.
The casts notations `T(e)` and `(T)e` are neither safe nor general.

##### Example

For built-in types, the construction notation protects against narrowing and reinterpretation

```cpp
void use(char ch, int i, double d, char* p, long long lng)
{
    int x1 = int{ch};     // OK, but redundant
    int x2 = int{d};      // error: double->int narrowing; use a cast if you need to
    int x3 = int{p};      // error: pointer to->int; use a reinterpret_cast if you really need to
    int x4 = int{lng};    // error: long long->int narrowing; use a cast if you need to

    int y1 = int(ch);     // OK, but redundant
    int y2 = int(d);      // bad: double->int narrowing; use a cast if you need to
    int y3 = int(p);      // bad: pointer to->int; use a reinterpret_cast if you really need to
    int y4 = int(lng);    // bad: long->int narrowing; use a cast if you need to

    int z1 = (int)ch;     // OK, but redundant
    int z2 = (int)d;      // bad: double->int narrowing; use a cast if you need to
    int z3 = (int)p;      // bad: pointer to->int; use a reinterpret_cast if you really need to
    int z4 = (int)lng;    // bad: long long->int narrowing; use a cast if you need to
}

```
The integer to/from pointer conversions are implementation defined when using the `T(e)` or `(T)e` notations, and non-portable
between platforms with different integer and pointer sizes.

##### Note

[Avoid casts](I-10-Expressions%20and%20Statements-ES.048.md#Res-casts) (explicit type conversion) and if you must [prefer named casts](I-10-Expressions%20and%20Statements-ES.049.md#Res-casts-named).

##### Note

When unambiguous, the `T` can be left out of `T{e}`.

```cpp
complex<double> f(complex<double>);

auto z = f({2*pi, 1});

```
##### Note

The construction notation is the most general [initializer notation](I-10-Expressions%20and%20Statements-ES.023.md#Res-list).

##### Exception

`std::vector` and other containers were defined before we had `{}` as a notation for construction.
Consider:

```cpp
vector<string> vs {10};                           // ten empty strings
vector<int> vi1 {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};  // ten elements 1..10
vector<int> vi2 {10};                             // one element with the value 10

```
How do we get a `vector` of 10 default initialized `int`s?

```cpp
vector<int> v3(10); // ten elements with value 0

```
The use of `()` rather than `{}` for number of elements is conventional (going back to the early 1980s), hard to change, but still
a design error: for a container where the element type can be confused with the number of elements, we have an ambiguity that
must be resolved.
The conventional resolution is to interpret `{10}` as a list of one element and use `(10)` to distinguish a size.

This mistake need not be repeated in new code.
We can define a type to represent the number of elements:

```cpp
struct Count { int n };

template<typename T>
class Vector {
public:
    Vector(Count n);                     // n default-initialized elements
    Vector(initializer_list<T> init);    // init.size() elements
    // ...
};

Vector<int> v1{10};
Vector<int> v2{Count{10}};
Vector<Count> v3{Count{10}};    // yes, there is still a very minor problem

```
The main problem left is to find a suitable name for `Count`.

##### Enforcement

Flag the C-style `(T)e` and functional-style `T(e)` casts.

## <a name="SS-numbers"></a>Arithmetic

