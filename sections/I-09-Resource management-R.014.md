### <a name="Rr-ap"></a>R.14: ??? array vs. pointer parameter

##### Reason

An array decays to a pointer, thereby losing its size, opening the opportunity for range errors.

##### Example

    ??? what do we recommend: f(int*[]) or f(int**) ???

**Alternative**: Use `span` to preserve size information.

##### Enforcement

Flag `[]` parameters.

