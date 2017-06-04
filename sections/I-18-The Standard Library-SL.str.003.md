### <a name="Rstr-zstring"></a>SL.str.3: Use `zstring` or `czstring` to refer to a C-style, zero-terminated, sequence of characters

##### Reason

Readability.
Statement of intent.
A plain `char*` can be a pointer to a single character, a pointer to an array of characters, a pointer to a C-style (zero terminated) string, or even to a small integer.
Distinguishing these alternatives prevents misunderstandings and bugs.

##### Example

```cpp
void f1(const char* s); // s is probably a string

```
All we know is that it is supposed to be the nullptr or point to at least one character

```cpp
void f1(zstring s);     // s is a C-style string or the nullptr
void f1(czstring s);    // s is a C-style string that is not the nullptr
void f1(std::byte* s);  // s is a pointer to a byte (C++17)

```
##### Note

Don't convert a C-style string to `string` unless there is a reason to.

##### Note

Like any other "plain pointer", a `zstring` should not represent ownership.

##### Note

There are billions of lines of C++ "out there", most use `char*` and `const char*` without documenting intent.
They are used in a wide variety of ways, including to represent ownership and as generic pointers to memory (instead of `void*`).
It is hard to separate these uses, so this guideline is hard to follow.
This is one of the major sources of bugs in C and C++ programs, so it is worthwhile to follow this guideline wherever feasible..

##### Enforcement

* Flag uses of `[]` on a `char*`
* Flag uses of `delete` on a `char*`
* Flag uses of `free()` on a `char*`

