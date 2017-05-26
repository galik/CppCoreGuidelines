### <a name="Re-exception-ref"></a>E.15: Catch exceptions from a hierarchy by reference

##### Reason

To prevent slicing.

##### Example

```cpp
void f()
try {
    // ...
}
catch (exception e) {   // don't: may slice
    // ...
}

```
Instead, use a reference:

```cpp
catch (exception& e) { /* ... */ }

```
of - typically better still - a `const` reference:

```cpp
catch (const exception& e) { /* ... */ }

```
Most handlers do not modify their exception and in general we [recommend use of `const`](I-10-Expressions%20and%20Statements-ES.025.md#Res-const).

##### Enforcement

Flag by-value exceptions if their types are part of a hierarchy (could require whole-program analysis to be perfect).

