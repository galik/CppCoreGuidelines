### <a name="Re-finally"></a>E.19: Use a `final_action` object to express cleanup if no suitable resource handle is available

##### Reason

`finally` is less verbose and harder to get wrong than `try`/`catch`.

##### Example

```cpp
void f(int n)
{
    void* p = malloc(1, n);
    auto _ = finally([p] { free(p); });
    // ...
}

```
##### Note

`finally` is not as messy as `try`/`catch`, but it is still ad-hoc.
Prefer [proper resource management objects](I-13-Error handling-E.006.md#Re-raii).
Consider `finally` a last resort.

##### Note

Use of `finally` is a systematic and reasonably clean alternative to the old [`goto exit;` technique](##Re-no-throw-codes)
for dealing with cleanup where resource management is not systematic.

##### Enforcement

Heuristic: Detect `goto exit;`

