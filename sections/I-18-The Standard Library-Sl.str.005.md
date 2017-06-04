### <a name="Rstr-byte"></a>Sl.str.5: Use `std::byte` to refer to byte values that do not necessarily represent characters

##### Reason

Use of `char*` to represent a pointer to something that is not necessarily a character causes confusion
and disables valuable optimizations.

##### Example

    ???

##### Note

C++17

##### Enforcement

???
    

