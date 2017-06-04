### <a name="Res-for-while"></a>ES.72: Prefer a `for`-statement to a `while`-statement when there is an obvious loop variable

##### Reason

Readability: the complete logic of the loop is visible "up front". The scope of the loop variable can be limited.

##### Example

```cpp
for (int i = 0; i < vec.size(); i++) {
    // do work
}

```
##### Example, bad

```cpp
int i = 0;
while (i < vec.size()) {
    // do work
    i++;
}

```
##### Enforcement

???

