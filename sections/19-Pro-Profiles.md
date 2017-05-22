

[INDEX](00-In-Introduction.md#SS-sec)

# <a name="S-profile"></a>Pro: Profiles

Ideally, we would follow all of the guidelines.
That would give the cleanest, most regular, least error-prone, and often the fastest code.
Unfortunately, that is usually impossible because we have to fit our code into large code bases and use existing libraries.
Often, such code has been written over decades and does not follow these guidelines.
We must aim for [gradual adoption](24-Appendix%20B-Modernizing%20code.md#S-modernizing).

Whatever strategy for gradual adoption we adopt, we need to be able to apply sets of related guidelines to address some set
of problems first and leave the rest until later.
A similar idea of "related guidelines" becomes important when some, but not all, guidelines are considered relevant to a code base
or if a set of specialized guidelines is to be applied for a specialized application area.
We call such a set of related guidelines a "profile".
We aim for such a set of guidelines to be coherent so that they together help us reach a specific goal, such as "absence of range errors"
or "static type safety."
Each profile is designed to eliminate a class of errors.
Enforcement of "random" rules in isolation is more likely to be disruptive to a code base than delivering a definite improvement.

A "profile" is a set of deterministic and portably enforceable subset rules (i.e., restrictions) that are designed to achieve a specific guarantee.
"Deterministic" means they require only local analysis and could be implemented in a compiler (though they don't need to be).
"Portably enforceable" means they are like language rules, so programmers can count on different enforcement tools giving the same answer for the same code.

Code written to be warning-free using such a language profile is considered to conform to the profile.
Conforming code is considered to be safe by construction with regard to the safety properties targeted by that profile.
Conforming code will not be the root cause of errors for that property,
although such errors may be introduced into a program by other code, libraries or the external environment.
A profile may also introduce additional library types to ease conformance and encourage correct code.

Profiles summary:

* [Pro.type: Type safety](19-Pro-Profiles.md#SS-type)
* [Pro.bounds: Bounds safety](19-Pro-Profiles.md#SS-bounds)
* [Pro.lifetime: Lifetime safety](19-Pro-Profiles.md#SS-lifetime)

In the future, we expect to define many more profiles and add more checks to existing profiles.
Candidates include:

* narrowing arithmetic promotions/conversions (likely part of a separate safe-arithmetic profile)
* arithmetic cast from negative floating point to unsigned integral type (ditto)
* selected undefined behavior: Start with Gabriel Dos Reis's UB list developed for the WG21 study group
* selected unspecified behavior: Addressing portability concerns.
* `const` violations: Mostly done by compilers already, but we can catch inappropriate casting and underuse of `const`.

Enabling a profile is implementation defined; typically, it is set in the analysis tool used.

To suppress enforcement of a profile check, place a `suppress` annotation on a language contract. For example:

```cpp
[[suppress(bounds)]] char* raw_find(char* p, int n, char x)    // find x in p[0]..p[n-1]
{
    // ...
}

```
Now `raw_find()` can scramble memory to its heart's content.
Obviously, suppression should be very rare.

## <a name="SS-type"></a>Pro.safety: Type-safety profile

This profile makes it easier to construct code that uses types correctly and avoids inadvertent type punning.
It does so by focusing on removing the primary sources of type violations, including unsafe uses of casts and unions.

For the purposes of this section,
type-safety is defined to be the property that a variable is not used in a way that doesn't obey the rules for the type of its definition.
Memory accessed as a type `T` should not be valid memory that actually contains an object of an unrelated type `U`.
Note that the safety is intended to be complete when combined also with [Bounds safety](19-Pro-Profiles.md#SS-bounds) and [Lifetime safety](19-Pro-Profiles.md#SS-lifetime).

An implementation of this profile shall recognize the following patterns in source code as non-conforming and issue a diagnostic.

Type safety profile summary:

* <a name="Pro-type-reinterpretcast"></a>Type.1: Don't use `reinterpret_cast`:
A strict version of [Avoid casts](07-ES-Expressions%20and%20Statements.md#Res-casts) and [prefer named casts](07-ES-Expressions%20and%20Statements.md#Res-casts-named).
* <a name="Pro-type-downcast"></a>Type.2: Don't use `static_cast` downcasts:
[Use `dynamic_cast` instead](04-C-Classes%20and%20Class%20Hierarchies.md#Rh-dynamic_cast).
* <a name="Pro-type-constcast"></a>Type.3: Don't use `const_cast` to cast away `const` (i.e., at all):
[Don't cast away const](07-ES-Expressions%20and%20Statements.md#Res-casts-const).
* <a name="Pro-type-cstylecast"></a>Type.4: Don't use C-style `(T)expression` casts:
[Prefer static casts](#Res-cast-named).
* [Type.4.1: Don't use `T(expression)` cast](19-Pro-Profiles.md#Pro-fct-style-cast):
[Prefer named casts](07-ES-Expressions%20and%20Statements.md#Res-casts-named).
* [Type.5: Don't use a variable before it has been initialized](#Pro-type-init):
[always initialize](07-ES-Expressions%20and%20Statements.md#Res-always).
* [Type.6: Always initialize a member variable](19-Pro-Profiles.md#Pro-type-memberinit):
[always initialize](07-ES-Expressions%20and%20Statements.md#Res-always),
possibly using [default constructors](04-C-Classes%20and%20Class%20Hierarchies.md#Rc-default0) or
[default member initializers](#Rc-in-class-initializers).
* [Type.7: Avoid naked union](19-Pro-Profiles.md#Pro-fct-style-cast):
[Use `variant` instead](04-C-Classes%20and%20Class%20Hierarchies.md#Ru-naked).
* [Type.8: Avoid varargs](#Pro-type-varargs):
[Don't use `va_arg` arguments](03-F-Functions.md#F-varargs).

##### Impact

With the type-safety profile you can trust that every operation is applied to a valid object.
Exception may be thrown to indicate errors that cannot be detected statically (at compile time).
Note that this type-safety can be complete only if we also have [Bounds safety](19-Pro-Profiles.md#SS-bounds) and [Lifetime safety](19-Pro-Profiles.md#SS-lifetime).
Without those guarantees, a region of memory could be accessed independent of which object, objects, or parts of objects are stored in it.

### <a name="Pro-fct-style-cast"></a>Type.4.1: Don't use `T(expression)` for casting.

##### Reason

If `e` is of a built-in type, `T(e)` is equivalent to the error-prone `(T)e`.

##### Example, bad

```cpp
int* p = f(x);
auto i = int(p);    // Potential damaging cast; don't or use `reinterpret_cast`

short s = short(i); // potentially narrowing; don't or use `narrow` or `narrow_cast`

```
##### Note

The {}-syntax makes the desire for construction explicit and doesn't allow narrowing

```cpp
f(Foo{bar});

```
##### Enforcement

Flag `T(e)` if used for `e` of a built-in type.


### <a name="Pro-type-memberinit"></a>Type.6: Always initialize a member variable.

##### Reason

Before a variable has been initialized, it does not contain a deterministic valid value of its type. It could contain any arbitrary bit pattern, which could be different on each call.

##### Example

```cpp
struct X { int i; };

X x;
use(x); // BAD, x has not been initialized

X x2{}; // GOOD
use(x2);

```
##### Enforcement

* Issue a diagnostic for any constructor of a non-trivially-constructible type that does not initialize all member variables. To fix: Write a data member initializer, or mention it in the member initializer list.
* Issue a diagnostic when constructing an object of a trivially constructible type without `()` or `{}` to initialize its members. To fix: Add `()` or `{}`.



## <a name="SS-bounds"></a>Pro.bounds: Bounds safety profile

This profile makes it easier to construct code that operates within the bounds of allocated blocks of memory. It does so by focusing on removing the primary sources of bounds violations: pointer arithmetic and array indexing. One of the core features of this profile is to restrict pointers to only refer to single objects, not arrays.

For the purposes of this document, bounds-safety is defined to be the property that a program does not use a variable to access memory outside of the range that was allocated and assigned to that variable. (Note that the safety is intended to be complete when combined also with [Type safety](19-Pro-Profiles.md#SS-type) and [Lifetime safety](19-Pro-Profiles.md#SS-lifetime), which cover other unsafe operations that allow bounds violations, such as type-unsafe casts that 'widen' pointers.)

The following are under consideration but not yet in the rules below, and may be better in other profiles:

* ???

An implementation of this profile shall recognize the following patterns in source code as non-conforming and issue a diagnostic.

Bounds safety profile summary:

* [Bounds.1: Don't use pointer arithmetic. Use `span` instead](19-Pro-Profiles.md#Pro-bounds-arithmetic)
* [Bounds.2: Only index into arrays using constant expressions](19-Pro-Profiles.md#Pro-bounds-arrayindex)
* [Bounds.3: No array-to-pointer decay](19-Pro-Profiles.md#Pro-bounds-decay)
* [Bounds.4: Don't use standard library functions and types that are not bounds-checked](19-Pro-Profiles.md#Pro-bounds-stdlib)


### <a name="Pro-bounds-arithmetic"></a>Bounds.1: Don't use pointer arithmetic. Use `span` instead.

##### Reason

Pointers should only refer to single objects, and pointer arithmetic is fragile and easy to get wrong. `span` is a bounds-checked, safe type for accessing arrays of data.

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
##### Enforcement

Issue a diagnostic for any arithmetic operation on an expression of pointer type that results in a value of pointer type.

### <a name="Pro-bounds-arrayindex"></a>Bounds.2: Only index into arrays using constant expressions.

##### Reason

Dynamic accesses into arrays are difficult for both tools and humans to validate as safe. `span` is a bounds-checked, safe type for accessing arrays of data. `at()` is another alternative that ensures single accesses are bounds-checked. If iterators are needed to access an array, use the iterators from a `span` constructed over the array.

##### Example, bad

```cpp
void f(array<int, 10> a, int pos)
{
    a[pos / 2] = 1; // BAD
    a[pos - 1] = 2; // BAD
    a[-1] = 3;    // BAD -- no replacement, just don't do this
    a[10] = 4;    // BAD -- no replacement, just don't do this
}

```
##### Example, good

```cpp
// ALTERNATIVE A: Use a span

// A1: Change parameter type to use span
void f1(span<int, 10> a, int pos)
{
    a[pos / 2] = 1; // OK
    a[pos - 1] = 2; // OK
}

// A2: Add local span and use that
void f2(array<int, 10> arr, int pos)
{
    span<int> a = {arr, pos}
    a[pos / 2] = 1; // OK
    a[pos - 1] = 2; // OK
}

// ALTERNATIVE B: Use at() for access
void f3(array<int, 10> a, int pos)
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

```cpp
// ALTERNATIVE A: Use a span
void f1()
{
    int arr[COUNT];
    span<int> av = arr;
    for (int i = 0; i < COUNT; ++i)
        av[i] = i;
}

// ALTERNATIVE Aa: Use a span and range-for
void f1a()
{
     int arr[COUNT];
     span<int, COUNT> av = arr;
     int i = 0;
     for (auto& e : av)
         e = i++;
}

// ALTERNATIVE B: Use at() for access
void f2()
{
    int arr[COUNT];
    for (int i = 0; i < COUNT; ++i)
        at(arr, i) = i;
}

```
##### Enforcement

Issue a diagnostic for any indexing expression on an expression or variable of array type (either static array or `std::array`) where the indexer is not a compile-time constant expression.

Issue a diagnostic for any indexing expression on an expression or variable of array type (either static array or `std::array`) where the indexer is not a value between `0` or and the upper bound of the array.

**Rewrite support**: Tooling can offer rewrites of array accesses that involve dynamic index expressions to use `at()` instead:

```cpp
static int a[10];

void f(int i, int j)
{
    a[i + j] = 12;      // BAD, could be rewritten as ...
    at(a, i + j) = 12;  // OK -- bounds-checked
}

```
### <a name="Pro-bounds-decay"></a>Bounds.3: No array-to-pointer decay.

##### Reason

Pointers should not be used as arrays. `span` is a bounds-checked, safe alternative to using pointers to access arrays.

##### Example, bad

```cpp
void g(int* p, size_t length);

void f()
{
    int a[5];
    g(a, 5);        // BAD
    g(&a[0], 1);    // OK
}

```
##### Example, good

```cpp
void g(int* p, size_t length);
void g1(span<int> av); // BETTER: get g() changed.

void f()
{
    int a[5];
    span<int> av = a;

    g(av.data(), av.length());   // OK, if you have no choice
    g1(a);                       // OK -- no decay here, instead use implicit span ctor
}

```
##### Enforcement

Issue a diagnostic for any expression that would rely on implicit conversion of an array type to a pointer type.

### <a name="Pro-bounds-stdlib"></a>Bounds.4: Don't use standard library functions and types that are not bounds-checked.

##### Reason

These functions all have bounds-safe overloads that take `span`. Standard types such as `vector` can be modified to perform bounds-checks under the bounds profile (in a compatible way, such as by adding contracts), or used with `at()`.

##### Example, bad

```cpp
void f()
{
    array<int, 10> a, b;
    memset(a.data(), 0, 10);         // BAD, and contains a length error (length = 10 * sizeof(int))
    memcmp(a.data(), b.data(), 10);  // BAD, and contains a length error (length = 10 * sizeof(int))
}

```
Also, `std::array<>::fill()` or `std::fill()` or even an empty initializer are better candidate than `memset()`.

##### Example, good

```cpp
void f()
{
    array<int, 10> a, b, c{};       // c is initialized to zero
    a.fill(0);
    fill(b.begin(), b.end(), 0);    // std::fill()
    fill(b, 0);                     // std::fill() + Ranges TS

    if ( a == b ) {
      // ...
    }
}

```
##### Example

If code is using an unmodified standard library, then there are still workarounds that enable use of `std::array` and `std::vector` in a bounds-safe manner. Code can call the `.at()` member function on each class, which will result in an `std::out_of_range` exception being thrown. Alternatively, code can call the `at()` free function, which will result in fail-fast (or a customized action) on a bounds violation.

```cpp
void f(std::vector<int>& v, std::array<int, 12> a, int i)
{
    v[0] = a[0];        // BAD
    v.at(0) = a[0];     // OK (alternative 1)
    at(v, 0) = a[0];    // OK (alternative 2)

    v.at(0) = a[i];     // BAD
    v.at(0) = a.at(i);  // OK (alternative 1)
    v.at(0) = at(a, i); // OK (alternative 2)
}

```
##### Enforcement

* Issue a diagnostic for any call to a standard library function that is not bounds-checked. ??? insert link to a list of banned functions

**TODO Notes**:

* Impact on the standard library will require close coordination with WG21, if only to ensure compatibility even if never standardized.
* We are considering specifying bounds-safe overloads for stdlib (especially C stdlib) functions like `memcmp` and shipping them in the GSL.
* For existing stdlib functions and types like `vector` that are not fully bounds-checked, the goal is for these features to be bounds-checked when called from code with the bounds profile on, and unchecked when called from legacy code, possibly using contracts (concurrently being proposed by several WG21 members).



## <a name="SS-lifetime"></a>Pro.lifetime: Lifetime safety profile

See /docs folder for the initial design. The detailed formal rules are in progress (as of May 2017).

The following are specific rules that are being enforced.

Lifetime safety profile summary:

* [Lifetime.1: Don't dereference a possibly invalid pointer.](19-Pro-Profiles.md#Pro-lifetime-invalid-deref)
* [Lifetime.2: Don't dereference a possibly null pointer.](19-Pro-Profiles.md#Pro-lifetime-null-deref)
* [Lifetime.3: Don't pass a possibly invalid pointer to a function.](19-Pro-Profiles.md#Pro-lifetime-invalid-argument)


### <a name="Pro-lifetime-invalid-deref"></a>Lifetime.1: Don't dereference a possibly invalid pointer.

##### Reason

It is undefined behavior.

To resolve the problem, either extend the lifetime of the object the pointer is intended to refer to, or shorten the lifetime of the pointer (move the dereference to before the pointed-to object's lifetime ends).

##### Example, bad

```cpp
void f()
{
    int x = 0;
    int* p = &x;

    if (condition()) {
        int y = 0;
        p = &y;
    } // invalidates p

    *p = 42;            // BAD, p might be invalid if the branch was taken
}

```
##### Example, good

```cpp
void f()
{
    int x = 0;
    int* p = &x;

    int y = 0;
    if (condition()) {
        p = &y;
    }

    *p = 42;            // OK, p points to x or y and both are still in scope
}

```
##### Enforcement

* Issue a diagnostic for any dereference of a pointer that could have been invalidated (could point to an object that was destroyed) along a local code path leading to the dereference. To fix: Extend the lifetime of the pointed-to object, or move the dereference to before the pointed-to object's lifetime ends.



### <a name="Pro-lifetime-null-deref"></a>Lifetime.2: Don't dereference a possibly null pointer.

##### Reason

It is undefined behavior.

##### Example, bad

```cpp
void f(int* p1)
{
    *p1 = 42;           // BAD, p1 might be null

    int i = 0;
    int* p2 = condition() ? &i : nullptr;
    *p2 = 42;           // BAD, p2 might be null
}

```
##### Example, good

```cpp
void f(int* p1, not_null<int*> p3)
{
    if (p1 != nullptr) {
        *p1 = 42;       // OK, must be not null in this branch
    }

    int i = 0;
    int* p2 = condition() ? &i : nullptr;
    if (p2 != nullptr) {
        *p2 = 42;       // OK, must be not null in this branch
    }

    *p3 = 42;           // OK, not_null does not need to be tested for nullness
}

```
##### Enforcement

* Issue a diagnostic for any dereference of a pointer that could have been set to null along a local code path leading to the dereference. To fix: Add a null check and dereference the pointer only in a branch that has tested to ensure non-null.



### <a name="Pro-lifetime-invalid-argument"></a>Lifetime.3: Don't pass a possibly invalid pointer to a function.

##### Reason

The function cannot do anything useful with the pointer.

To resolve the problem, either extend the lifetime of the object the pointer is intended to refer to, or shorten the lifetime of the pointer (move the function call to before the pointed-to object's lifetime ends).

##### Example, bad

```cpp
void f(int*);

void g()
{
    int x = 0;
    int* p = &x;

    if (condition()) {
        int y = 0;
        p = &y;
    } // invalidates p

    f(p);               // BAD, p might be invalid if the branch was taken
}

```
##### Example, good

```cpp
void f()
{
    int x = 0;
    int* p = &x;

    int y = 0;
    if (condition()) {
        p = &y;
    }

    f(p);               // OK, p points to x or y and both are still in scope
}

```
##### Enforcement

* Issue a diagnostic for any function argument that is a pointer that could have been invalidated (could point to an object that was destroyed) along a local code path leading to the dereference. To fix: Extend the lifetime of the pointed-to object, or move the function call to before the pointed-to object's lifetime ends.





[INDEX](00-In-Introduction.md#SS-sec)

