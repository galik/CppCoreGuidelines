### <a name="Res-casts-const"></a>ES.50: Don't cast away `const`

##### Reason

It makes a lie out of `const`.
If the variable is actually declared `const`, the result of "casting away `const`" is undefined behavior.

##### Example, bad

```cpp
void f(const int& i)
{
    const_cast<int&>(i) = 42;   // BAD
}

static int i = 0;
static const int j = 0;

f(i); // silent side effect
f(j); // undefined behavior

```
##### Example

Sometimes, you may be tempted to resort to `const_cast` to avoid code duplication, such as when two accessor functions that differ only in `const`-ness have similar implementations. For example:

```cpp
class Bar;

class Foo {
public:
    // BAD, duplicates logic
    Bar& get_bar() {
        /* complex logic around getting a non-const reference to my_bar */
    }

    const Bar& get_bar() const {
        /* same complex logic around getting a const reference to my_bar */
    }
private:
    Bar my_bar;
};

```
Instead, prefer to share implementations. Normally, you can just have the non-`const` function call the `const` function. However, when there is complex logic this can lead to the following pattern that still resorts to a `const_cast`:

```cpp
class Foo {
public:
    // not great, non-const calls const version but resorts to const_cast
    Bar& get_bar() {
        return const_cast<Bar&>(static_cast<const Foo&>(*this).get_bar());
    }
    const Bar& get_bar() const {
        /* the complex logic around getting a const reference to my_bar */
    }
private:
    Bar my_bar;
};

```
Although this pattern is safe when applied correctly, because the caller must have had a non-`const` object to begin with, it's not ideal because the safety is hard to enforce automatically as a checker rule.

Instead, prefer to put the common code in a common helper function -- and make it a template so that it deduces `const`. This doesn't use any `const_cast` at all:

```cpp
class Foo {
public:                         // good
          Bar& get_bar()       { return get_bar_impl(*this); }
    const Bar& get_bar() const { return get_bar_impl(*this); }
private:
    Bar my_bar;

    template<class T>           // good, deduces whether T is const or non-const
    static auto get_bar_impl(T& t) -> decltype(t.get_bar())
        { /* the complex logic around getting a possibly-const reference to my_bar */ }
};

```
##### Exception

You may need to cast away `const` when calling `const`-incorrect functions.
Prefer to wrap such functions in inline `const`-correct wrappers to encapsulate the cast in one place.

##### Example

Sometimes, "cast away `const`" is to allow the updating of some transient information of an otherwise immutable object.
Examples are caching, memoization, and precomputation.
Such examples are often handled as well or better using `mutable` or an indirection than with a `const_cast`.

Consider keeping previously computed results around for a costly operation:

```cpp
int compute(int x); // compute a value for x; assume this to be costly

class Cache {   // some type implementing a cache for an int->int operation
public:
    pair<bool, int> find(int x) const;   // is there a value for x?
    void set(int x, int v);             // make y the value for x
    // ...
private:
    // ...
};

class X {
public:
    int get_val(int x)
    {
        auto p = cache.find(x);
        if (p.first) return p.second;
        int val = compute(x);
        cache.set(x, val); // insert value for x
        return val;
    }
    // ...
private:
    Cache cache;
};

```
Here, `get_val()` is logically constant, so we would like to make it a `const` member.
To do this we still need to mutate `cache`, so people sometimes resort to a `const_cast`:

```cpp
class X {   // Suspicious solution based on casting
public:
    int get_val(int x) const
    {
        auto p = cache.find(x);
        if (p.first) return p.second;
        int val = compute(x);
        const_cast<Cache&>(cache).set(x, val);   // ugly
        return val;
    }
    // ...
private:
    Cache cache;
};

```
Fortunately, there is a better solution:
State that `cache` is mutable even for a `const` object:

```cpp
class X {   // better solution
public:
    int get_val(int x) const
    {
        auto p = cache.find(x);
        if (p.first) return p.second;
        int val = compute(x);
        cache.set(x, val);
        return val;
    }
    // ...
private:
    mutable Cache cache;
};

```
An alternative solution would to store a pointer to the `cache`:

```cpp
class X {   // OK, but slightly messier solution
public:
    int get_val(int x) const
    {
        auto p = cache->find(x);
        if (p.first) return p.second;
        int val = compute(x);
        cache->set(x, val);
        return val;
    }
    // ...
private:
    unique_ptr<Cache> cache;
};

```
That solution is the most flexible, but requires explicit construction and destruction of `*cache`
(most likely in the constructor and destructor of `X`).

In any variant, we must guard against data races on the `cache` in multithreaded code, possibly using a `std::mutex`.

##### Enforcement

* Flag `const_cast`s.
* This rule is part of the [type-safety profile](I-22-Profiles.md#Pro-type-constcast) for the related Profile.

