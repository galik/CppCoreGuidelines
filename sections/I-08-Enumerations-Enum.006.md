### <a name="Renum-unnamed"></a>Enum.6: Avoid unnamed enumerations

##### Reason

If you can't name an enumeration, the values are not related

##### Example, bad

```cpp
enum { red = 0xFF0000, scale = 4, is_signed = 1 };

```
Such code is not uncommon in code written before there were convenient alternative ways of specifying integer constants.

##### Alternative

Use `constexpr` values instead. For example:

```cpp
constexpr int red = 0xFF0000;
constexpr short scale = 4;
constexpr bool is_signed = true;

```
##### Enforcement

Flag unnamed enumerations.


