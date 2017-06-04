### <a name="Rstr-char*"></a>SL.str.4: Use `char*` to refer to a single character

##### Reason

The variety of uses of `char*` in current code is a major source of errors.

##### Example, bad

```cpp
char arr[] = {'a', 'b', 'c'};

void print(const char* p)
{
    cout << p << '\n';
}

void use()
{
    print(arr);   // run-time error; potentially very bad
}

```
The array `arr` is not a C-style string because it is not zero-terminated.

##### Alternative

See [`zstring`](I-18-The%20Standard%20Library-SL.str.003.md#Rstr-zstring), [`string`](I-18-The%20Standard%20Library-SL.str.001.md#Rstr-string), and [`string_span`](I-18-The%20Standard%20Library-SL.str.002.md#Rstr-view).

##### Enforcement

* Flag uses of `[]` on a `char*`

