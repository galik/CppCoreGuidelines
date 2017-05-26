### <a name="Rc-swap-noexcept"></a>C.85: Make `swap` `noexcept`

##### Reason

 [A `swap` may not fail](I-07-Constructors, assignments, and destructors-C.084.md#Rc-swap-fail).
If a `swap` tries to exit with an exception, it's a bad design error and the program had better terminate.

##### Enforcement

(Simple) When a class has a `swap` member function, it should be declared `noexcept`.

