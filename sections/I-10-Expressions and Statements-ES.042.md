### <a name="Res-ptr"></a>ES.42: Keep use of pointers simple and straightforward

##### Reason

Complicated pointer manipulation is a major source of errors.

##### Note

Use `gsl::span` instead.
Pointers should [only refer to single objects](I-04-Interfaces-I.013.md#Ri-array).
Pointer arithmetic is fragile and easy to get wrong, the source of many, many bad bugs and security violations.
`span` is a bounds-checked, safe type for accessing arrays of data.
Access into an array with known bounds using a constant as a subscript can be validated by the compiler.

##### Example, bad

```cpp
void f(int* p, int count)
{
    if (count < 2) return;

    int* q = p + 1; // BAD

    ptrdiff_t d;
    int n;
    d = (p - &n); // OK
    d = (q - p); // OK

    int n = *p++; // BAD

    if (count < 6) return;

    p[4] = 1; // BAD

    p[count - 1] = 2; // BAD

    use(&p[0], 3); // BAD
}

```
##### Example, good

```cpp
void f(span<int> a) // BETTER: use span in the function declaration
{
    if (a.length() < 2) return;

    int n = a[0]; // OK

    span<int> q = a.subspan(1); // OK

    if (a.length() < 6) return;

    a[4] = 1; // OK

    a[count - 1] = 2; // OK

    use(a.data(), 3); // OK
}

```
##### Note

Subscripting with a variable is difficult for both tools and humans to validate as safe.
`span` is a run-time bounds-checked, safe type for accessing arrays of data.
`at()` is another alternative that ensures single accesses are bounds-checked.
If iterators are needed to access an array, use the iterators from a `span` constructed over the array.

##### Example, bad

```cpp
void f(array<int, 10> a, int pos)
{
    a[pos / 2] = 1; // BAD
    a[pos - 1] = 2; // BAD
    a[-1] = 3;    // BAD (but easily caught by tools) -- no replacement, just don't do this
    a[10] = 4;    // BAD (but easily caught by tools) -- no replacement, just don't do this
}

```
##### Example, good

Use a `span`:

```cpp
void f1(span<int, 10> a, int pos) // A1: Change parameter type to use span
{
    a[pos / 2] = 1; // OK
    a[pos - 1] = 2; // OK
}

void f2(array<int, 10> arr, int pos) // A2: Add local span and use that
{
    span<int> a = {arr, pos}
    a[pos / 2] = 1; // OK
    a[pos - 1] = 2; // OK
}

```
Use a `at()`:

```cpp
void f3(array<int, 10> a, int pos) // ALTERNATIVE B: Use at() for access
{
    at(a, pos / 2) = 1; // OK
    at(a, pos - 1) = 2; // OK
}

```
##### Example, bad

```cpp
void f()
{
    int arr[COUNT];
    for (int i = 0; i < COUNT; ++i)
        arr[i] = i; // BAD, cannot use non-constant indexer
}

```
##### Example, good

Use a `span`:

```cpp
void f1()
{
    int arr[COUNT];
    span<int> av = arr;
    for (int i = 0; i < COUNT; ++i)
        av[i] = i;
}

```
Use a `span` and range-`for`:

```cpp
void f1a()
{
     int arr[COUNT];
     span<int, COUNT> av = arr;
     int i = 0;
     for (auto& e : av)
         e = i++;
}

```
Use `at()` for access:

```cpp
void f2()
{
    int arr[COUNT];
    for (int i = 0; i < COUNT; ++i)
        at(arr, i) = i;
}

```
Use a range-`for`:

```cpp
void f3()
{
    int arr[COUNT];
    for (auto& e : arr)
         e = i++;
}

```
##### Note

Tooling can offer rewrites of array accesses that involve dynamic index expressions to use `at()` instead:

```cpp
static int a[10];

void f(int i, int j)
{
    a[i + j] = 12;      // BAD, could be rewritten as ...
    at(a, i + j) = 12;  // OK -- bounds-checked
}

```
##### Example

Turning an array into a pointer (as the language does essentially always) removes opportunities for checking, so avoid it

```cpp
void g(int* p);

void f()
{
    int a[5];
    g(a);        // BAD: are we trying to pass an array?
    g(&a[0]);    // OK: passing one object
}

```
If you want to pass an array, say so:

```cpp
void g(int* p, size_t length);  // old (dangerous) code

void g1(span<int> av); // BETTER: get g() changed.

void f2()
{
    int a[5];
    span<int> av = a;

    g(av.data(), av.length());   // OK, if you have no choice
    g1(a);                       // OK -- no decay here, instead use implicit span ctor
}

```
##### Enforcement

* Flag any arithmetic operation on an expression of pointer type that results in a value of pointer type.
* Flag any indexing expression on an expression or variable of array type (either static array or `std::array`) where the indexer is not a compile-time constant expression with a value between `0` or and the upper bound of the array.
* Flag any expression that would rely on implicit conversion of an array type to a pointer type.

This rule is part of the [bounds-safety profile](I-22-Profiles.md#SS-bounds).


