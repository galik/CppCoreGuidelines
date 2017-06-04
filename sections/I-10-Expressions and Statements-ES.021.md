### <a name="Res-introduce"></a>ES.21: Don't introduce a variable (or constant) before you need to use it

##### Reason

Readability. To limit the scope in which the variable can be used.

##### Example

```cpp
int x = 7;
// ... no use of x here ...
++x;

```
##### Enforcement

Flag declarations that are distant from their first use.

