### <a name="Res-zero"></a>ES.105: Don't divide by zero

##### Reason

The result is undefined and probably a crash.

##### Note

This also applies to `%`.

##### Example; bad

```cpp
double divide(int a, int b) {
    // BAD, should be checked (e.g., in a precondition)
    return a / b;
}

```
##### Example; good

```cpp
double divide(int a, int b) {
    // good, address via precondition (and replace with contracts once C++ gets them)
    Expects(b != 0);
    return a / b;
}

double divide(int a, int b) {
    // good, address via check
    return b ? a / b : quiet_NaN<double>();
}

```
**Alternative**: For critical applications that can afford some overhead, use a range-checked integer and/or floating-point type.

##### Enforcement

* Flag division by an integral value that could be zero


