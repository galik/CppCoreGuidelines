### <a name="Ru-pun"></a>C.183: Don't use a `union` for type punning

##### Reason

It is undefined behavior to read a `union` member with a different type from the one with which it was written.
Such punning is invisible, or at least harder to spot than using a named cast.
Type punning using a `union` is a source of errors.

##### Example, bad

```cpp
union Pun {
    int x;
    unsigned char c[sizeof(int)];
};

```
The idea of `Pun` is to be able to look at the character representation of an `int`.

```cpp
void bad(Pun& u)
{
    u.x = 'x';
    cout << u.c[0] << '\n';     // undefined behavior
}

```
If you wanted to see the bytes of an `int`, use a (named) cast:

```cpp
void if_you_must_pun(int& x)
{
    auto p = reinterpret_cast<unsigned char*>(&x);
    cout << p[0] << '\n';     // OK; better
    // ...
}

```
Accessing the result of an `reinterpret_cast` to a different type from the objects declared type is defined behavior (even though `reinterpret_cast` is discouraged),
but at least we can see that something tricky is going on.

##### Note

Unfortunately, `union`s are commonly used for type punning.
We don't consider "sometimes, it works as expected" a strong argument.

C++17 introduced a distinct type `std::byte` to facilitate operations on raw object representation.  Use that type instead of `unsigned char` or `char` for these operations.

##### Enforcement

???



