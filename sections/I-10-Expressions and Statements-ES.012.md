### <a name="Res-reuse"></a>ES.12: Do not reuse names in nested scopes

##### Reason

It is easy to get confused about which variable is used.
Can cause maintenance problems.

##### Example, bad

```cpp
int d = 0;
// ...
if (cond) {
    // ...
    d = 9;
    // ...
}
else {
    // ...
    int d = 7;
    // ...
    d = value_to_be_returned;
    // ...
}

return d;

```
If this is a large `if`-statement, it is easy to overlook that a new `d` has been introduced in the inner scope.
This is a known source of bugs.
Sometimes such reuse of a name in an inner scope is called "shadowing".

##### Note

Shadowing is primarily a problem when functions are too large and too complex.

##### Example

Shadowing of function arguments in the outermost block is disallowed by the language:

```cpp
void f(int x)
{
    int x = 4;  // error: reuse of function argument name

    if (x) {
        int x = 7;  // allowed, but bad
        // ...
    }
}

```
##### Example, bad

Reuse of a member name as a local variable can also be a problem:

```cpp
struct S {
    int m;
    void f(int x);
};

void S::f(int x)
{
    m = 7;    // assign to member
    if (x) {
        int m = 9;
        // ...
        m = 99; // assign to member
        // ...
    }
}

```
##### Exception

We often reuse function names from a base class in a derived class:

```cpp
struct B {
    void f(int);
};

struct D : B {
    void f(double);
    using B::f;
};

```
This is error-prone.
For example, had we forgotten the using declaration, a call `d.f(1)` would not have found the `int` version of `f`.

??? Do we need a specific rule about shadowing/hiding in class hierarchies?

##### Enforcement

* Flag reuse of a name in nested local scopes
* Flag reuse of a member name as a local variable in a member function
* Flag reuse of a global name as a local variable or a member name
* Flag reuse of a base class member name in a derived class (except for function names)

