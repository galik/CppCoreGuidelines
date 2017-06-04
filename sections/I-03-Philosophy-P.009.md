### <a name="Rp-waste"></a>P.9: Don't waste time or space

##### Reason

This is C++.

##### Note

Time and space that you spend well to achieve a goal (e.g., speed of development, resource safety, or simplification of testing) is not wasted.
"Another benefit of striving for efficiency is that the process forces you to understand the problem in more depth." - Alex Stepanov

##### Example, bad

```cpp
struct X {
    char ch;
    int i;
    string s;
    char ch2;

    X& operator=(const X& a);
    X(const X&);
};

X waste(const char* p)
{
    if (p == nullptr) throw Nullptr_error{};
    int n = strlen(p);
    auto buf = new char[n];
    if (buf == nullptr) throw Allocation_error{};
    for (int i = 0; i < n; ++i) buf[i] = p[i];
    // ... manipulate buffer ...
    X x;
    x.ch = 'a';
    x.s = string(n);    // give x.s space for *p
    for (int i = 0; i < x.s.size(); ++i) x.s[i] = buf[i];  // copy buf into x.s
    delete buf;
    return x;
}

void driver()
{
    X x = waste("Typical argument");
    // ...
}

```
Yes, this is a caricature, but we have seen every individual mistake in production code, and worse.
Note that the layout of `X` guarantees that at least 6 bytes (and most likely more) are wasted.
The spurious definition of copy operations disables move semantics so that the return operation is slow
(please note that the Return Value Optimization, RVO, is not guaranteed here).
The use of `new` and `delete` for `buf` is redundant; if we really needed a local string, we should use a local `string`.
There are several more performance bugs and gratuitous complication.

##### Example, bad

```cpp
void lower(zstring s)
{
    for (int i = 0; i < strlen(s); ++i) s[i] = tolower(s[i]);
}

```
Yes, this is an example from production code.
We leave it to the reader to figure out what's wasted.

##### Note

An individual example of waste is rarely significant, and where it is significant, it is typically easily eliminated by an expert.
However, waste spread liberally across a code base can easily be significant and experts are not always as available as we would like.
The aim of this rule (and the more specific rules that support it) is to eliminate most waste related to the use of C++ before it happens.
After that, we can look at waste related to algorithms and requirements, but that is beyond the scope of these guidelines.

##### Enforcement

Many more specific rules aim at the overall goals of simplicity and elimination of gratuitous waste.

