### <a name="Rt-concept-def"></a>T.48: If your compiler does not support concepts, fake them with `enable_if`

##### Reason

Because that's the best we can do without direct concept support.
`enable_if` can be used to conditionally define functions and to select among a set of functions.

##### Example

```cpp
enable_if<???>

```
##### Note

Beware of [complementary constraints](# T.25).
Faking concept overloading using `enable_if` sometimes forces us to use that error-prone design technique.

##### Enforcement

???

