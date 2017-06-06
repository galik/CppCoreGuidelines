### <a name="Rh-mi-implementation"></a>C.136: Use multiple inheritance to represent the union of implementation attributes

##### Reason

Some forms of mixins have state and often operations on that state.
If the operations are virtual the use of inheritance is necessary, if not using inheritance can avoid boilerplate and forwarding.

##### Example

```cpp
  class iostream : public istream, public ostream {   // very simplified
    // ...
};

```
`istream` provides the interface to input operations (and some data); `ostream` provides the interface to output operations (and some data).
`iostream` provides the union of the `istream` and `ostream` interfaces and the synchronization needed to allow both on a single stream.

##### Note

This a relatively rare use because implementation can often be organized into a single-rooted hierarchy.

##### Example

Sometimes, an "implementation attribute" is more like a "mixin" that determine the behavior of an implementation and inject
members to enable the implementation of the policies it requires.
For example, see `std::enable_shared_from_this`
or various bases from boost.intrusive (e.g. `list_base_hook` or `intrusive_ref_counter`).

##### Enforcement

???

