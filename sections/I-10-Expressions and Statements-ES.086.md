### <a name="Res-loop-counter"></a>ES.86: Avoid modifying loop control variables inside the body of raw for-loops

##### Reason

The loop control up front should enable correct reasoning about what is happening inside the loop. Modifying loop counters in both the iteration-expression and inside the body of the loop is a perennial source of surprises and bugs.

##### Example

```cpp
for (int i = 0; i < 10; ++i) {
    // no updates to i -- ok
}

for (int i = 0; i < 10; ++i) {
    //
    if (/* something */) ++i; // BAD
    //
}

bool skip = false;
for (int i = 0; i < 10; ++i) {
    if (skip) { skip = false; continue; }
    //
    if (/* something */) skip = true;  // Better: using two variable for two concepts.
    //
}

```
##### Enforcement

Flag variables that are potentially updated (have a non-const use) in both the loop control iteration-expression and the loop body.

## ES.expr: Expressions

Expressions manipulate values.

