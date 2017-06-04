### <a name="Renum-value"></a>Enum.8: Specify enumerator values only when necessary

##### Reason

It's the simplest.
It avoids duplicate enumerator values.
The default gives a consecutive set of values that is good for `switch`-statement implementations.

##### Example

```cpp
enum class Col1 { red, yellow, blue };
enum class Col2 { red = 1, yellow = 2, blue = 2 }; // typo
enum class Month { jan = 1, feb, mar, apr, may, jun,
                   jul, august, sep, oct, nov, dec }; // starting with 1 is conventional
enum class Base_flag { dec = 1, oct = dec << 1, hex = dec << 2 }; // set of bits

```
Specifying values is necessary to match conventional values (e.g., `Month`)
and where consecutive values are undesirable (e.g., to get separate bits as in `Base_flag`).

##### Enforcement

* Flag duplicate enumerator values
* Flag explicitly specified all-consecutive enumerator values


