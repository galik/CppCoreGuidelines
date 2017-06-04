### <a name="Rc-dtor-ptr"></a>C.32: If a class has a raw pointer (`T*`) or reference (`T&`), consider whether it might be owning

##### Reason

There is a lot of code that is non-specific about ownership.

##### Example

    ???

##### Note

If the `T*` or `T&` is owning, mark it `owning`. If the `T*` is not owning, consider marking it `ptr`.
This will aid documentation and analysis.

##### Enforcement

Look at the initialization of raw member pointers and member references and see if an allocation is used.

