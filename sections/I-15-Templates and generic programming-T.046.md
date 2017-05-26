### <a name="Rt-regular"></a>T.46: Require template arguments to be at least `Regular` or `SemiRegular`

##### Reason

 Readability.
 Preventing surprises and errors.
 Most uses support that anyway.

##### Example

```cpp
class X {
        // ...
public:
    explicit X(int);
    X(const X&);            // copy
    X operator=(const X&);
    X(X&&);                 // move
    X& operator=(X&&);
    ~X();
    // ... no more constructors ...
};

X x {1};    // fine
X y = x;      // fine
std::vector<X> v(10); // error: no default constructor

```
##### Note

Semiregular requires default constructible.

##### Enforcement

* Flag types that are not at least `SemiRegular`.

