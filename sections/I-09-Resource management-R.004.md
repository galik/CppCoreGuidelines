### <a name="Rr-ref"></a>R.4: A raw reference (a `T&`) is non-owning

##### Reason

There is nothing (in the C++ standard or in most code) to say otherwise and most raw references are non-owning.
We want owners identified so that we can reliably and efficiently delete the objects pointed to by owning pointers.

##### Example

```cpp
void f()
{
    int& r = *new int{7};  // bad: raw owning reference
    // ...
    delete &r;             // bad: violated the rule against deleting raw pointers
}

```
**See also**: [The raw pointer rule](I-09-Resource%20management-R.003.md#Rr-ptr)

##### Enforcement

See [the raw pointer rule](I-09-Resource%20management-R.003.md#Rr-ptr)

