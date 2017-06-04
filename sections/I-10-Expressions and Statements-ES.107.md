### <a name="Res-subscripts"></a>ES.107: Don't use `unsigned` for subscripts

##### Reason

To avoid signed/unsigned confusion.
To enable better optimization.
To enable better error detection.

##### Example, bad

```cpp
vector<int> vec {1, 2, 3, 4, 5};

for (int i = 0; i < vec.size(); i += 2)                    // mix int and unsigned
    cout << vec[i] << '\n';
for (unsigned i = 0; i < vec.size(); i += 2)               // risk wraparound
    cout << vec[i] << '\n';
for (vector<int>::size_type i = 0; i < vec.size(); i += 2) // verbose
    cout << vec[i] << '\n';
for (auto i = 0; i < vec.size(); i += 2)                   // mix int and unsigned
    cout << vec[i] << '\n';

```
##### Note

The built-in array uses signed subscripts.
The standard-library containers use unsigned subscripts.
Thus, no perfect and fully compatible solution is possible.
Given the known problems with unsigned and signed/unsigned mixtures, better stick to (signed) integers.

##### Example

```cpp
template<typename T>
struct My_container {
public:
    // ...
    T& operator[](int i);    // not unsigned
    // ...
};

```
##### Example

```cpp
??? demonstrate improved code generation and potential for error detection ???

```
##### Alternatives

Alternatives for users

* use algorithms
* use range-for
* use iterators/pointers

##### Enforcement

Very tricky as long as the standard-library containers get it wrong.

