### <a name="Re-not-always"></a>E.17: Don't try to catch every exception in every function

##### Reason

Catching an exception in a function that cannot take a meaningful recovery action leads to complexity and waste.
Let an exception propagate until it reaches a function that can handle it.
Let cleanup actions on the unwinding path be handled by [RAII](I-13-Error%20handling-E.006.md#Re-raii).

##### Example, don't

```cpp
void f()   // bad
{
    try {
        // ...
    }
    catch (...) {
        // no action
        throw;   // propagate exception
    }
}

```
##### Enforcement

* Flag nested try-blocks.
* Flag source code files with a too high ratio of try-blocks to functions. (??? Problem: define "too high")

