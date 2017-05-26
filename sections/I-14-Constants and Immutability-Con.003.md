### <a name="Rconst-ref"></a>Con.3: By default, pass pointers and references to `const`s

##### Reason

 To avoid a called function unexpectedly changing the value.
 It's far easier to reason about programs when called functions don't modify state.

##### Example

```cpp
void f(char* p);        // does f modify *p? (assume it does)
void g(const char* p);  // g does not modify *p

```
##### Note

It is not inherently bad to pass a pointer or reference to non-const,
but that should be done only when the called function is supposed to modify the object.

##### Note

[Do not cast away `const`](I-10-Expressions and Statements-ES.050.md#Res-casts-const).

##### Enforcement

* Flag function that does not modify an object passed by  pointer or reference to non-`const`
* Flag a function that (using a cast) modifies an object passed by pointer or reference to `const`

