### <a name="Rc-explicit"></a>C.46: By default, declare single-argument constructors explicit

##### Reason

To avoid unintended conversions.

##### Example, bad

```cpp
class String {
    // ...
public:
    String(int);   // BAD
    // ...
};

String s = 10;   // surprise: string of size 10

```
##### Exception

If you really want an implicit conversion from the constructor argument type to the class type, don't use `explicit`:

```cpp
class Complex {
    // ...
public:
    Complex(double d);   // OK: we want a conversion from d to {d, 0}
    // ...
};

Complex z = 10.7;   // unsurprising conversion

```
**See also**: [Discussion of implicit conversions](I-07-Constructors%2C%20assignments%2C%20and%20destructors-C.164.md#Ro-conversion).

##### Enforcement

(Simple) Single-argument constructors should be declared `explicit`. Good single argument non-`explicit` constructors are rare in most code based. Warn for all that are not on a "positive list".

