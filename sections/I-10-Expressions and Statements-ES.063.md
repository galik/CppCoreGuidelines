### <a name="Res-slice"></a>ES.63: Don't slice

##### Reason

Slicing -- that is, copying only part of an object using assignment or initialization -- most often leads to errors because
the object was meant to be considered as a whole.
In the rare cases where the slicing was deliberate the code can be surprising.

##### Example

```cpp
class Shape { /* ... */ };
class Circle : public Shape { /* ... */ Point c; int r; };

Circle c {{0, 0}, 42};
Shape s {c};    // copy Shape part of Circle

```
The result will be meaningless because the center and radius will not be copied from `c` into `s`.
The first defense against this is to [define the base class `Shape` not to allow this](I-07-Constructors%2C%20assignments%2C%20and%20destructors-C.067.md#Rc-copy-virtual).

##### Alternative

If you mean to slice, define an explicit operation to do so.
This saves readers from confusion.
For example:

```cpp
class Smiley : public Circle {
    public:
    Circle copy_circle();
    // ...
};

Smiley sm { /* ... */ };
Circle c1 {sm};  // ideally prevented by the definition of Circle
Circle c2 {sm.copy_circle()};

```
##### Enforcement

Warn against slicing.

