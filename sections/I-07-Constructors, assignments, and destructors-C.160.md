### <a name="Ro-conventional"></a>C.160: Define operators primarily to mimic conventional usage

##### Reason

Minimize surprises.

##### Example

```cpp
class X {
public:
    // ...
    X& operator=(const X&); // member function defining assignment
    friend bool operator==(const X&, const X&); // == needs access to representation
                                                // after a = b we have a == b
    // ...
};

```
Here, the conventional semantics is maintained: [Copies compare equal](I-07-Constructors%2C%20assignments%2C%20and%20destructors-C.052.md#SS-copy).

##### Example, bad

```cpp
X operator+(X a, X b) { return a.v - b.v; }   // bad: makes + subtract

```
##### Note

Non-member operators should be either friends or defined in [the same namespace as their operands](I-07-Constructors%2C%20assignments%2C%20and%20destructors-C.168.md#Ro-namespace).
[Binary operators should treat their operands equivalently](I-07-Constructors%2C%20assignments%2C%20and%20destructors-C.161.md#Ro-symmetric).

##### Enforcement

Possibly impossible.

