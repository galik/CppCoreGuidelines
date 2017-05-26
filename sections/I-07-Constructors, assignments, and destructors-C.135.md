### <a name="Rh-mi-interface"></a>C.135: Use multiple inheritance to represent multiple distinct interfaces

##### Reason

Not all classes will necessarily support all interfaces, and not all callers will necessarily want to deal with all operations.
Especially to break apart monolithic interfaces into "aspects" of behavior supported by a given derived class.

##### Example

```cpp
class iostream : public istream, public ostream {   // very simplified
    // ...
};

```
`istream` provides the interface to input operations; `ostream` provides the interface to output operations.
`iostream` provides the union of the `istream` and `ostream` interfaces and the synchronization needed to allow both on a single stream. 

##### Note

This is a very common use of inheritance because the need for multiple different interfaces to an implementation is common
and such interfaces are often not easily or naturally organized into a single-rooted hierarchy.

##### Note

Such interfaces are typically abstract classes.

##### Enforcement

???

