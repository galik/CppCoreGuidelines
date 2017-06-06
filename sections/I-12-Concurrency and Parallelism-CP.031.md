### <a name="Rconc-data-by-value"></a>CP.31: Pass small amounts of data between threads by value, rather than by reference or pointer

##### Reason

Copying a small amount of data is cheaper to copy and access than to share it using some locking mechanism.
Copying naturally gives unique ownership (simplifies code) and eliminates the possibility of data races.

##### Note

Defining "small amount" precisely is impossible.

##### Example

```cpp
string modify1(string);
void modify2(shared_ptr<string>);

void fct(string& s)
{
    auto res = async(modify1, s);
    async(modify2, &s);
}

```
The call of `modify1` involves copying two `string` values; the call of `modify2` does not.
On the other hand, the implementation of `modify1` is exactly as we would have written it for single-threaded code,
whereas the implementation of `modify2` will need some form of locking to avoid data races.
If the string is short (say 10 characters), the call of `modify1` can be surprisingly fast;
essentially all the cost is in the `thread` switch. If the string is long (say 1,000,000 characters), copying it twice
is probably not a good idea.

Note that this argument has nothing to do with `sync` as such. It applies equally to considerations about whether to use
message passing or shared memory.

##### Enforcement

???


