### <a name="Rnr-single-return"></a>NR.2: Don't: Have only a single `return`-statement in a function

##### Reason (not to follow this rule)

The single-return rule can lead to unnecessarily convoluted code and the introduction of extra state variables.
In particular, the single-return rule makes it harder to concentrate error checking at the top of a function.

##### Example

```cpp
template<class T>
//  requires Number<T>
string sign(T x)
{
    if (x < 0)
        return "negative";
    else if (x > 0)
        return "positive";
    return "zero";
}

```
to use a single return only we would have to do something like

```cpp
template<class T>
//  requires Number<T>
string sign(T x)        // bad
{
    string res;
    if (x < 0)
        res = "negative";
    else if (x > 0)
        res = "positive";
    else
        res = "zero";
    return res;
}

```
This is both longer and likely to be less efficient.
The larger and more complicated the function is, the more painful the workarounds get.
Of course many simple functions will naturally have just one `return` because of their simpler inherent logic.

##### Example

```cpp
int index(const char* p)
{
    if (p == nullptr) return -1;  // error indicator: alternatively "throw nullptr_error{}"
    // ... do a lookup to find the index for p
    return i;
}

```
If we applied the rule, we'd get something like

```cpp
int index2(const char* p)
{
    int i;
    if (p == nullptr)
        i = -1;  // error indicator
    else {
        // ... do a lookup to find the index for p
    }
    return i;
}

```
Note that we (deliberately) violated the rule against uninitialized variables because this style commonly leads to that.
Also, this style is a temptation to use the [goto exit](I-20-Non-Rules%20and%20myths-NR.006.md#Rnr-goto-exit) non-rule.

##### Alternative

* Keep functions short and simple
* Feel free to use multiple `return` statements (and to throw exceptions).

