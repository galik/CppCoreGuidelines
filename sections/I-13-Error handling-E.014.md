### <a name="Re-exception-types"></a>E.14: Use purpose-designed user-defined types as exceptions (not built-in types)

##### Reason

A user-defined type is unlikely to clash with other people's exceptions.

##### Example

```cpp
void my_code()
{
    // ...
    throw Moonphase_error{};
    // ...
}

void your_code()
{
    try {
        // ...
        my_code();
        // ...
    }
    catch(Bufferpool_exhausted) {
        // ...
    }
}

```
##### Example, don't

```cpp
void my_code()     // Don't
{
    // ...
    throw 7;       // 7 means "moon in the 4th quarter"
    // ...
}

void your_code()   // Don't
{
    try {
        // ...
        my_code();
        // ...
    }
    catch(int i) {  // i == 7 means "input buffer too small"
        // ...
    }
}

```
##### Note

The standard-library classes derived from `exception` should be used only as base classes or for exceptions that require only "generic" handling. Like built-in types, their use could clash with other people's use of them.

##### Example, don't

```cpp
void my_code()   // Don't
{
    // ...
    throw runtime_error{"moon in the 4th quarter"};
    // ...
}

void your_code()   // Don't
{
    try {
        // ...
        my_code();
        // ...
    }
    catch(runtime_error) {   // runtime_error means "input buffer too small"
        // ...
    }
}

```
**See also**: [Discussion](#Sd-???)

##### Enforcement

Catch `throw` and `catch` of a built-in type. Maybe warn about `throw` and `catch` using an standard-library `exception` type. Obviously, exceptions derived from the `std::exception` hierarchy is fine.

