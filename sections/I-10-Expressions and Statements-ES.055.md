### <a name="Res-range-checking"></a>ES.55: Avoid the need for range checking

##### Reason

Constructs that cannot overflow do not overflow (and usually run faster):

##### Example

```cpp
for (auto& x : v)      // print all elements of v
    cout << x << '\n';

auto p = find(v, x);   // find x in v

```
##### Enforcement

Look for explicit range checks and heuristically suggest alternatives.

