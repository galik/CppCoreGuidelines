### <a name="Rr-reseat"></a>R.33: Take a `unique_ptr<widget>&` parameter to express that a function reseats the`widget`

##### Reason

Using `unique_ptr` in this way both documents and enforces the function call's reseating semantics.

##### Note

"reseat" means "making a pointer or a smart pointer refer to a different object."

##### Example

```cpp
void reseat(unique_ptr<widget>&); // "will" or "might" reseat pointer

```
##### Example, bad

```cpp
void thinko(const unique_ptr<widget>&); // usually not what you want

```
##### Enforcement

* (Simple) Warn if a function takes a `Unique_ptr<T>` parameter by lvalue reference and does not either assign to it or call `reset()` on it on at least one code path. Suggest taking a `T*` or `T&` instead.
* (Simple) ((Foundation)) Warn if a function takes a `Unique_ptr<T>` parameter by reference to `const`. Suggest taking a `const T*` or `const T&` instead.

