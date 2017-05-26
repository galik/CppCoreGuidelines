### <a name="Rc-class"></a>C.8: Use `class` rather than `struct` if any member is non-public

##### Reason

Readability.
To make it clear that something is being hidden/abstracted.
This is a useful convention.

##### Example, bad

```cpp
struct Date {
    int d, m;

    Date(int i, Month m);
    // ... lots of functions ...
private:
    int y;  // year
};

```
There is nothing wrong with this code as far as the C++ language rules are concerned,
but nearly everything is wrong from a design perspective.
The private data is hidden far from the public data.
The data is split in different parts of the class declaration.
Different parts of the data have different access.
All of this decreases readability and complicates maintenance.

##### Note

Prefer to place the interface first in a class [see](I-24-Naming and layout rules-NL.016.md#Rl-order).

##### Enforcement

Flag classes declared with `struct` if there is a `private` or `public` member.

