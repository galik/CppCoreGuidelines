### <a name="Res-for-init"></a>ES.74: Prefer to declare a loop variable in the initializer part of a `for`-statement

##### Reason

Limit the loop variable visibility to the scope of the loop.
Avoid using the loop variable for other purposes after the loop.

##### Example

```cpp
for (int i = 0; i < 100; ++i) {   // GOOD: i var is visible only inside the loop
    // ...
}

```
##### Example, don't

```cpp
int j;                            // BAD: j is visible outside the loop
for (j = 0; j < 100; ++j) {
    // ...
}
// j is still visible here and isn't needed

```
**See also**: [Don't use a variable for two unrelated purposes](I-10-Expressions%20and%20Statements-ES.026.md#Res-recycle)

##### Example

```cpp
for (string s; cin >> s; ) {
    cout << s << '\n';
}

```
##### Enforcement

Warn when a variable modified inside the `for`-statement is declared outside the loop and not being used outside the loop.

**Discussion**: Scoping the loop variable to the loop body also helps code optimizers greatly. Recognizing that the induction variable
is only accessible in the loop body unblocks optimizations such as hoisting, strength reduction, loop-invariant code motion, etc.

