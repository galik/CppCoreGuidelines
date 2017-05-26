### <a name="Rio-sync"></a>SL.io.10: Unless you use `printf`-family functions call `ios_base::sync_with_stdio(false)`

##### Reason

Synchronizing `iostreams` with `printf-style` I/O can be costly.
`cin` and `cout` are by default synchronized with `printf`.

##### Example

```cpp
int main()
{
    ios_base::sync_with_stdio(false);
    // ... use iostreams ...
}

```
##### Enforcement

???

