### <a name="Rc-zero"></a>C.20: If you can avoid defining default operations, do

##### Reason

It's the simplest and gives the cleanest semantics.

##### Example

```cpp
struct Named_map {
public:
    // ... no default operations declared ...
private:
    string name;
    map<int, int> rep;
};

Named_map nm;        // default construct
Named_map nm2 {nm};  // copy construct

```
Since `std::map` and `string` have all the special functions, no further work is needed.

##### Note

This is known as "the rule of zero".

##### Enforcement

(Not enforceable) While not enforceable, a good static analyzer can detect patterns that indicate a possible improvement to meet this rule.
For example, a class with a (pointer, size) pair of member and a destructor that `delete`s the pointer could probably be converted to a `vector`.

