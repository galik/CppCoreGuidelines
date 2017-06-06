### <a name="Rh-array"></a>C.152: Never assign a pointer to an array of derived class objects to a pointer to its base

##### Reason

Subscripting the resulting base pointer will lead to invalid object access and probably to memory corruption.

##### Example

```cpp
struct B { int x; };
struct D : B { int y; };

void use(B*);

D a[] = {{1, 2}, {3, 4}, {5, 6}};
B* p = a;     // bad: a decays to &a[0] which is converted to a B*
p[1].x = 7;   // overwrite D[0].y

use(a);       // bad: a decays to &a[0] which is converted to a B*

```
##### Enforcement

* Flag all combinations of array decay and base to derived conversions.
* Pass an array as a `span` rather than as a pointer, and don't let the array name suffer a derived-to-base conversion before getting into the `span`


