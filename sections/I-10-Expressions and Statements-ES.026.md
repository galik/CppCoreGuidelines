### <a name="Res-recycle"></a>ES.26: Don't use a variable for two unrelated purposes

##### Reason

Readability and safety.

##### Example, bad

```cpp
void use()
{
    int i;
    for (i = 0; i < 20; ++i) { /* ... */ }
    for (i = 0; i < 200; ++i) { /* ... */ } // bad: i recycled
}

```
##### Note

As an optimization, you may want to reuse a buffer as a scratch pad, but even then prefer to limit the variable's scope as much as possible and be careful not to cause bugs from data left in a recycled buffer as this is a common source of security bugs.

```cpp
void write_to_file() {
    std::string buffer;             // to avoid reallocations on every loop iteration
    for (auto& o : objects)
    {
        // First part of the work.
        generate_first_String(buffer, o);
        write_to_file(buffer);

        // Second part of the work.
        generate_second_string(buffer, o);
        write_to_file(buffer);

        // etc...
    }
}

```
##### Enforcement

Flag recycled variables.

