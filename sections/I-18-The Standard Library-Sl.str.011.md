### <a name="Rstr-span"></a>Sl.str.11: Use `gsl::string_span` rather than `std::string_view` when you need to mutate a string

##### Reason

`std::string_view` is read-only.

##### Example

???

##### Note

???

##### Enforcement

The compiler will flag attempts to write to a `string_view`.

