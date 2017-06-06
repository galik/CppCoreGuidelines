### <a name="Res-order"></a>ES.43: Avoid expressions with undefined order of evaluation

##### Reason

You have no idea what such code does. Portability.
Even if it does something sensible for you, it may do something different on another compiler (e.g., the next release of your compiler) or with a different optimizer setting.

##### Note

C++17 tightens up the rules for the order of evaluation:
left-to-right except right-to-left in assignments, and the order of evaluation of function arguments is unspecified.

However, remember that your code may be compiled with a pre-C++17 compiler (e.g., through cut-and-paste) so don't be too clever.

##### Example

```cpp
v[i] = ++i;   //  the result is undefined

```
A good rule of thumb is that you should not read a value twice in an expression where you write to it.

##### Enforcement

Can be detected by a good analyzer.

