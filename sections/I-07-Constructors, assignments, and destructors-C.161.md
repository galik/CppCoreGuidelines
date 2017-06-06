### <a name="Ro-symmetric"></a>C.161: Use nonmember functions for symmetric operators

##### Reason

If you use member functions, you need two.
Unless you use a non-member function for (say) `==`, `a == b` and `b == a` will be subtly different.

##### Example

```cpp
bool operator==(Point a, Point b) { return a.x == b.x && a.y == b.y; }

```
##### Enforcement

Flag member operator functions.

