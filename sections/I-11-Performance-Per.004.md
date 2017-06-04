### <a name="Rper-simple"></a>Per.4: Don't assume that complicated code is necessarily faster than simple code

##### Reason

Simple code can be very fast. Optimizers sometimes do marvels with simple code

##### Example, good

```cpp
// clear expression of intent, fast execution

vector<uint8_t> v(100000);

for (auto& c : v)
    c = ~c;

```
##### Example, bad

```cpp
// intended to be faster, but is actually slower

vector<uint8_t> v(100000);

for (size_t i = 0; i < v.size(); i += sizeof(uint64_t))
{
    uint64_t& quad_word = *reinterpret_cast<uint64_t*>(&v[i]);
    quad_word = ~quad_word;
}

```
##### Note

???

???

