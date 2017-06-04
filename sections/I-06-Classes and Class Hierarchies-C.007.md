### <a name="Rc-standalone"></a>C.7: Don't define a class or enum and declare a variable of its type in the same statement

##### Reason

Mixing a type definition and the definition of another entity in the same declaration is confusing and unnecessary.

##### Example; bad

```cpp
struct Data { /*...*/ } data{ /*...*/ };

```
##### Example; good

```cpp
struct Data { /*...*/ };
Data data{ /*...*/ };

```
##### Enforcement

* Flag if the `}` of a class or enumeration definition is not followed by a `;`. The `;` is missing.

