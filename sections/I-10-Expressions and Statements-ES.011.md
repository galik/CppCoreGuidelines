### <a name="Res-auto"></a>ES.11: Use `auto` to avoid redundant repetition of type names

##### Reason

* Simple repetition is tedious and error prone.
* When you use `auto`, the name of the declared entity is in a fixed position in the declaration, increasing readability.
* In a template function declaration the return type can be a member type.

##### Example

Consider:

```cpp
auto p = v.begin();   // vector<int>::iterator
auto s = v.size();
auto h = t.future();
auto q = make_unique<int[]>(s);
auto f = [](int x){ return x + 10; };

```
In each case, we save writing a longish, hard-to-remember type that the compiler already knows but a programmer could get wrong.

##### Example

```cpp
template<class T>
auto Container<T>::first() -> Iterator;   // Container<T>::Iterator

```
##### Exception

Avoid `auto` for initializer lists and in cases where you know exactly which type you want and where an initializer might require conversion.

##### Example

```cpp
auto lst = { 1, 2, 3 };   // lst is an initializer list
auto x{1};   // x is an int (after correction of the C++14 standard; initializer_list in C++11)

```
##### Note

When concepts become available, we can (and should) be more specific about the type we are deducing:

```cpp
// ...
ForwardIterator p = algo(x, y, z);

```
##### Example (C++17)

```cpp
auto [ quotient, remainder ] = div(123456, 73);   // break out the members of the div_t result

```
##### Enforcement

Flag redundant repetition of type names in a declaration.

