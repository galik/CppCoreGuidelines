### <a name="Rr-make_shared"></a>R.22: Use `make_shared()` to make `shared_ptr`s

##### Reason

If you first make an object and then give it to a `shared_ptr` constructor, you (most likely) do one more allocation (and later deallocation) than if you use `make_shared()` because the reference counts must be allocated separately from the object.

##### Example

Consider:

```cpp
shared_ptr<X> p1 { new X{2} }; // bad
auto p = make_shared<X>(2);    // good

```
The `make_shared()` version mentions `X` only once, so it is usually shorter (as well as faster) than the version with the explicit `new`.

##### Enforcement

(Simple) Warn if a `shared_ptr` is constructed from the result of `new` rather than `make_shared`.

