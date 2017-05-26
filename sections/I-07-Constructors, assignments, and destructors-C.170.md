### <a name="Ro-lambda"></a>C.170: If you feel like overloading a lambda, use a generic lambda

##### Reason

You cannot overload by defining two different lambdas with the same name.

##### Example

```cpp
void f(int);
void f(double);
auto f = [](char);   // error: cannot overload variable and function

auto g = [](int) { /* ... */ };
auto g = [](double) { /* ... */ };   // error: cannot overload variables

auto h = [](auto) { /* ... */ };   // OK

```
##### Enforcement

The compiler catches the attempt to overload a lambda.

## <a name="SS-union"></a>C.union: Unions

A `union` is a `struct` where all members start at the same address so that it can hold only one member at a time.
A `union` does not keep track of which member is stored so the programmer has to get it right;
this is inherently error-prone, but there are ways to compensate.

A type that is a `union` plus an indicator of which member is currently held is called a *tagged union*, a *discriminated union*, or a *variant*.

Union rule summary:

* [C.180: Use `union`s to save Memory](I-07-Constructors%2C%20assignments%2C%20and%20destructors-C.180.md#Ru-union)
* [C.181: Avoid "naked" `union`s](I-07-Constructors%2C%20assignments%2C%20and%20destructors-C.181.md#Ru-naked)
* [C.182: Use anonymous `union`s to implement tagged unions](I-07-Constructors%2C%20assignments%2C%20and%20destructors-C.182.md#Ru-anonymous)
* [C.183: Don't use a `union` for type punning](I-07-Constructors%2C%20assignments%2C%20and%20destructors-C.183.md#Ru-pun)
* ???

