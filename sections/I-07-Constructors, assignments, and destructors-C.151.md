### <a name="Rh-make_shared"></a>C.151: Use `make_shared()` to construct objects owned by `shared_ptr`s

##### Reason

 `make_shared` gives a more concise statement of the construction.
It also gives an opportunity to eliminate a separate allocation for the reference counts, by placing the `shared_ptr`'s use counts next to its object.

##### Example

```cpp
// OK: but repetitive; and separate allocations for the Foo and shared_ptr's use count
shared_ptr<Foo> p {new<Foo>{7}};

auto q = make_shared<Foo>(7);   // Better: no repetition of Foo; one object

```
##### Enforcement

* Flag the repetitive usage of template specialization list`<Foo>`
* Flag variables declared to be `shared_ptr<Foo>`

