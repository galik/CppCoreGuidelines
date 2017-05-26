### <a name="Rh-protected"></a>C.133: Avoid `protected` data

##### Reason

`protected` data is a source of complexity and errors.
`protected` data complicated the statement of invariants.
`protected` data inherently violates the guidance against putting data in base classes, which usually leads to having to deal virtual inheritance as well.

##### Example, bad

   class Shape {
   public:
```cpp
    // ... interface functions ...
rotected:
    // data for use in derived classes:
    Color fill_color;
    Color edge_color;
    Style st;
;

```
Now it is up to every derived `Shape` to manipulate the protected data correctly.
This has been popular, but also a major source of maintenance problems.
In a large class hierarchy, the consistent use of protected data is hard to maintain because there can be a lot of code,
spread over a lot of classes.
The set of classes that can touch that data is open: anyone can derive a new class and start manipulating the protected data.
Often, it is not possible to examine the complete set of classes so any change to the representation of the class becomes infeasible.
There is no enforced invariant for the protected data; it is much like a set of global variables.
The protected data has de facto become global to a large body of code.

##### Note

Protected data often looks tempting to enable arbitrary improvements through derivation.
Often, what you get is unprincipled changes and errors.
[Prefer `private` data](I-06-Classes%20and%20Class%20Hierarchies-C.009.md#Rc-private) with a well-specified and enforced invariant.
Alternative, and often better, [keep data out of any class used as an interface](I-07-Constructors%2C%20assignments%2C%20and%20destructors-C.121.md#Rh-abstract).

##### Note

Protected member function can be just fine.

##### Enforcement

Flag classes with `protected` data.

