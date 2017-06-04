### <a name="Rstr-byte"></a>SL.str.5: Use `std::byte` to refer to byte values that do not necessarily represent characters

##### Reason

Use of `char*` to represent a pointer to something that is not necessarily a character causes confusion
and disables valuable optimizations.

##### Example

```cpp
???

```
##### Note

C++17

##### Enforcement

???


