### <a name="Rc-dtor-noexcept"></a>C.37: Make destructors `noexcept`

##### Reason

 [A destructor may not fail](I-07-Constructors%2C%20assignments%2C%20and%20destructors-C.036.md#Rc-dtor-fail). If a destructor tries to exit with an exception, it's a bad design error and the program had better terminate.

##### Note

A destructor (either user-defined or compiler-generated) is implicitly declared `noexcept` (independently of what code is in its body) if all of the members of its class have `noexcept` destructors. By explicitly marking destructors `noexcept`, an author guards against the destructor becoming implicitly `noexcept(false)` through the addition or modification of a class member.

##### Enforcement

(Simple) A destructor should be declared `noexcept` if it could throw.

## <a name="SS-ctor"></a>C.ctor: Constructors

A constructor defines how an object is initialized (constructed).

