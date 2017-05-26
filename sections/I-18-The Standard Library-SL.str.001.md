### <a name="Rstr-string"></a>SL.str.1: Use `std::string` to own character sequences

##### Reason

`string` correctly handles allocation, ownership, copying, gradual expansion, and offers a variety of useful operations.

##### Example

```cpp
vector<string> read_until(const string& terminator)
{
    vector<string> res;
    for (string s; cin >> s && s != terminator; ) // read a word
        res.push_back(s);
    return res;
}

```
Note how `>>` and `!=` are provided for `string` (as examples of useful operations) and there are no explicit
allocations, deallocations, or range checks (`string` takes care of those).

In C++17, we might use `string_view` as the argument, rather than `const string*` to allow more flexibility to callers:

```cpp
vector<string> read_until(string_view terminator)   // C++17
{
    vector<string> res;
    for (string s; cin >> s && s != terminator; ) // read a word
        res.push_back(s);
    return res;
}

```
The `gsl::string_span` is a current alternative offering most of the benefits of `string_span` for simple examples:

```cpp
vector<string> read_until(string_span terminator)
{
    vector<string> res;
    for (string s; cin >> s && s != terminator; ) // read a word
        res.push_back(s);
    return res;
}

```
##### Example, bad

Don't use C-style strings for operations that require non-trivial memory management

```cpp
char* cat(const char* s1, const char* s2)   // beware!
    // return s1 + '.' + s2
{
    int l1 = strlen(s1);
    int l2 = strlen(s2);
    char* p = (char*)malloc(l1+l2+2);
    strcpy(p, s1, l1);
    p[l1] = '.';
    strcpy(p+l1+1, s2, l2);
    p[l1+l2+1] = 0;
    return res;
}

```
Did we get that right?
Will the caller remember to `free()` the returned pointer?
Will this code pass a security review?

##### Note

Do not assume that `string` is slower than lower-level techniques without measurement and remember than not all code is performance critical.
[Don't optimize prematurely](I-11-Performance-Per.002.md#Rper-Knuth)

##### Enforcement

???

