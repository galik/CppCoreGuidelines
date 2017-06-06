### <a name="Rc-copy-semantic"></a>C.61: A copy operation should copy

##### Reason

That is the generally assumed semantics. After `x = y`, we should have `x == y`.
After a copy `x` and `y` can be independent objects (value semantics, the way non-pointer built-in types and the standard-library types work) or refer to a shared object (pointer semantics, the way pointers work).

##### Example

```cpp
class X {   // OK: value semantics
public:
    X();
    X(const X&);     // copy X
    void modify();   // change the value of X
    // ...
    ~X() { delete[] p; }
private:
    T* p;
    int sz;
};

bool operator==(const X& a, const X& b)
{
    return a.sz == b.sz && equal(a.p, a.p + a.sz, b.p, b.p + b.sz);
}

X::X(const X& a)
    :p{new T[a.sz]}, sz{a.sz}
{
    copy(a.p, a.p + sz, a.p);
}

X x;
X y = x;
if (x != y) throw Bad{};
x.modify();
if (x == y) throw Bad{};   // assume value semantics

```
##### Example

```cpp
class X2 {  // OK: pointer semantics
public:
    X2();
    X2(const X&) = default; // shallow copy
    ~X2() = default;
    void modify();          // change the value of X
    // ...
private:
    T* p;
    int sz;
};

bool operator==(const X2& a, const X2& b)
{
    return a.sz == b.sz && a.p == b.p;
}

X2 x;
X2 y = x;
if (x != y) throw Bad{};
x.modify();
if (x != y) throw Bad{};  // assume pointer semantics

```
##### Note

Prefer copy semantics unless you are building a "smart pointer". Value semantics is the simplest to reason about and what the standard library facilities expect.

##### Enforcement

(Not enforceable)

