### <a name="Rt-lambda"></a>T.141: Use an unnamed lambda if you need a simple function object in one place only

##### Reason

That makes the code concise and gives better locality than alternatives.

##### Example

```cpp
auto earlyUsersEnd = std::remove_if(users.begin(), users.end(),
                                    [](const User &a) { return a.id > 100; });


```
##### Exception

Naming a lambda can be useful for clarity even if it is used only once.

##### Enforcement

* Look for identical and near identical lambdas (to be replaced with named functions or named lambdas).

