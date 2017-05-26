### <a name="Rt-tmp"></a>T.122: Use templates (usually template aliases) to compute types at compile time

##### Reason

Template metaprogramming is the only directly supported and half-way principled way of generating types at compile time.

##### Note

"Traits" techniques are mostly replaced by template aliases to compute types and `constexpr` functions to compute values.

##### Example

```cpp
??? big object / small object optimization

```
##### Enforcement

???

