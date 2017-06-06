### <a name="Res-name-length"></a>ES.7: Keep common and local names short, and keep uncommon and nonlocal names longer

##### Reason

Readability. Lowering the chance of clashes between unrelated non-local names.

##### Example

Conventional short, local names increase readability:

```cpp
template<typename T>    // good
void print(ostream& os, const vector<T>& v)
{
    for (int i = 0; i < v.size(); ++i)
        os << v[i] << '\n';
}

```
An index is conventionally called `i` and there is no hint about the meaning of the vector in this generic function, so `v` is as good name as any. Compare

```cpp
template<typename Element_type>   // bad: verbose, hard to read
void print(ostream& target_stream, const vector<Element_type>& current_vector)
{
    for (int current_element_index = 0;
            current_element_index < current_vector.size();
            ++current_element_index
    )
    target_stream << current_vector[current_element_index] << '\n';
}

```
Yes, it is a caricature, but we have seen worse.

##### Example

Unconventional and short non-local names obscure code:

```cpp
void use1(const string& s)
{
    // ...
    tt(s);   // bad: what is tt()?
    // ...
}

```
Better, give non-local entities readable names:

```cpp
void use1(const string& s)
{
    // ...
    trim_tail(s);   // better
    // ...
}

```
Here, there is a chance that the reader knows what `trim_tail` means and that the reader can remember it after looking it up.

##### Example, bad

Argument names of large functions are de facto non-local and should be meaningful:

```cpp
void complicated_algorithm(vector<Record>& vr, const vector<int>& vi, map<string, int>& out)
// read from events in vr (marking used Records) for the indices in
// vi placing (name, index) pairs into out
{
    // ... 500 lines of code using vr, vi, and out ...
}

```
We recommend keeping functions short, but that rule isn't universally adhered to and naming should reflect that.

##### Enforcement

Check length of local and non-local names. Also take function length into account.

