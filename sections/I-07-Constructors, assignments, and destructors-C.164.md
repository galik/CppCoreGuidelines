### <a name="Ro-conversion"></a>C.164: Avoid conversion operators

##### Reason

Implicit conversions can be essential (e.g., `double` to `int`) but often cause surprises (e.g., `String` to C-style string).

##### Note

Prefer explicitly named conversions until a serious need is demonstrated.
By "serious need" we mean a reason that is fundamental in the application domain (such as an integer to complex number conversion)
and frequently needed. Do not introduce implicit conversions (through conversion operators or non-`explicit` constructors)
just to gain a minor convenience.

##### Example, bad

```cpp
class String {   // handle ownership and access to a sequence of characters
    // ...
    String(czstring p); // copy from *p to *(this->elem)
    // ...
    operator zstring() { return elem; }
    // ...
};

void user(zstring p)
{
    if (*p == "") {
        String s {"Trouble ahead!"};
        // ...
        p = s;
    }
    // use p
}

```
The string allocated for `s` and assigned to `p` is destroyed before it can be used.

##### Enforcement

Flag all conversion operators.

