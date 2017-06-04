### <a name="Rr-make_unique"></a>R.23: Use `make_unique()` to make `unique_ptr`s

##### Reason

For convenience and consistency with `shared_ptr`.

##### Note

`make_unique()` is C++14, but widely available (as well as simple to write).

##### Enforcement

(Simple) Warn if a `unique_ptr` is constructed from the result of `new` rather than `make_unique`.

