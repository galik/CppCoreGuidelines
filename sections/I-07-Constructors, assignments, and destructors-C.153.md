### <a name="Rh-use-virtual"></a>C.153: Prefer virtual function to casting

##### Reason

A virtual function call is safe, whereas casting is error-prone.
A virtual function call reaches the most derived function, whereas a cast may reach an intermediate class and therefore
give a wrong result (especially as a hierarchy is modified during maintenance).

##### Example

    ???

##### Enforcement

See [C.146](I-07-Constructors%2C%20assignments%2C%20and%20destructors-C.146.md#Rh-dynamic_cast) and ???

## <a name="SS-overload"></a>C.over: Overloading and overloaded operators

You can overload ordinary functions, template functions, and operators.
You cannot overload function objects.

Overload rule summary:

* [C.160: Define operators primarily to mimic conventional usage](I-07-Constructors%2C%20assignments%2C%20and%20destructors-C.160.md#Ro-conventional)
* [C.161: Use nonmember functions for symmetric operators](I-07-Constructors%2C%20assignments%2C%20and%20destructors-C.161.md#Ro-symmetric)
* [C.162: Overload operations that are roughly equivalent](I-07-Constructors%2C%20assignments%2C%20and%20destructors-C.162.md#Ro-equivalent)
* [C.163: Overload only for operations that are roughly equivalent](I-07-Constructors%2C%20assignments%2C%20and%20destructors-C.163.md#Ro-equivalent-2)
* [C.164: Avoid conversion operators](I-07-Constructors%2C%20assignments%2C%20and%20destructors-C.164.md#Ro-conversion)
* [C.165: Use `using` for customization points](I-07-Constructors%2C%20assignments%2C%20and%20destructors-C.165.md#Ro-custom)
* [C.166: Overload unary `&` only as part of a system of smart pointers and references](I-07-Constructors%2C%20assignments%2C%20and%20destructors-C.166.md#Ro-address-of)
* [C.167: Use an operator for an operation with its conventional meaning](I-07-Constructors%2C%20assignments%2C%20and%20destructors-C.167.md#Ro-overload)
* [C.168: Define overloaded operators in the namespace of their operands](I-07-Constructors%2C%20assignments%2C%20and%20destructors-C.168.md#Ro-namespace)
* [C.170: If you feel like overloading a lambda, use a generic lambda](I-07-Constructors%2C%20assignments%2C%20and%20destructors-C.170.md#Ro-lambda)

