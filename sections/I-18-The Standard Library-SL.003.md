### <a name="sl-std"></a>SL.3: Do not add non-standard entities to namespace `std`

##### Reason

Adding to `std` may change the meaning of otherwise standards conforming code.
Additions to `std` may clash with future versions of the standard.

##### Example

```cpp
???

```
##### Enforcement

Possible, but messy and likely to cause problems with platforms.

