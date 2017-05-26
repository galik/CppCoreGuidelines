### <a name="Res-continue"></a>ES.77: Minimize the use of `break` and `continue` in loops

##### Reason

 In a non-trivial loop body, it is easy to overlook a `break` or a `continue`.

 A `break` in a loop has a dramatically different meaning than a `break` in a `switch`-statement
 (and you can have `switch`-statement in a loop and a loop in a `switch`-case).

##### Example

```cpp
???

```
##### Alternative

Often, a loop that requires a `break` is a good candidate for a function (algorithm), in which case the `break` becomes a `return`.

```cpp
???

```
Often. a loop that uses `continue` can equivalently and as clearly be expressed by an `if`-statement.

```cpp
???

```
##### Note

If you really need to break out a loop, a `break` is typically better than alternatives such as [modifying the loop variable](I-10-Expressions%20and%20Statements-ES.086.md#Res-loop-counter) or a [`goto`](I-10-Expressions%20and%20Statements-ES.076.md#Res-goto):


##### Enforcement

???

