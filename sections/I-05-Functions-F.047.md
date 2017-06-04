### <a name="Rf-assignment-op"></a>F.47: Return `T&` from assignment operators

##### Reason

The convention for operator overloads (especially on value types) is for
`operator=(const T&)` to perform the assignment and then return (non-const)
`*this`.  This ensures consistency with standard library types and follows the
principle of "do as the ints do."

##### Note

Historically there was some guidance to make the assignment operator return `const T&`.
This was primarily to avoid code of the form `(a = b) = c` -- such code is not common enough to warrant violating consistency with standard types.

##### Example

```cpp
class Foo
{
 public:
    ...
    Foo& operator=(const Foo& rhs) {
      // Copy members.
      ...
      return *this;
    }
};

```
##### Enforcement

This should be enforced by tooling by checking the return type (and return
value) of any assignment operator.

