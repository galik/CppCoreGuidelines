### <a name="Rr-weak_ptr"></a>R.24: Use `std::weak_ptr` to break cycles of `shared_ptr`s

##### Reason

 `shared_ptr`'s rely on use counting and the use count for a cyclic structure never goes to zero, so we need a mechanism to
be able to destroy a cyclic structure.

##### Example

    ???

##### Note

 ??? (HS: A lot of people say "to break cycles", while I think "temporary shared ownership" is more to the point.)
???(BS: breaking cycles is what you must do; temporarily sharing ownership is how you do it.
You could "temporarily share ownership" simply by using another `shared_ptr`.)

##### Enforcement

??? probably impossible. If we could statically detect cycles, we wouldn't need `weak_ptr`

