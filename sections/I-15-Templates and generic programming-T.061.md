### <a name="Rt-scary"></a>T.61: Do not over-parameterize members (SCARY)

##### Reason

A member that does not depend on a template parameter cannot be used except for a specific template argument.
This limits use and typically increases code size.

##### Example, bad

```cpp
template<typename T, typename A = std::allocator{}>
    // requires Regular<T> && Allocator<A>
class List {
public:
    struct Link {   // does not depend on A
        T elem;
        T* pre;
        T* suc;
    };

    using iterator = Link*;

    iterator first() const { return head; }

    // ...
private:
    Link* head;
};

List<int> lst1;
List<int, My_allocator> lst2;

???

```
This looks innocent enough, but ???

```cpp
template<typename T>
struct Link {
    T elem;
    T* pre;
    T* suc;
};

template<typename T, typename A = std::allocator{}>
    // requires Regular<T> && Allocator<A>
class List2 {
public:
    using iterator = Link<T>*;

    iterator first() const { return head; }

    // ...
private:
    Link* head;
};

List<int> lst1;
List<int, My_allocator> lst2;

???

```
##### Enforcement

* Flag member types that do not depend on every template argument
* Flag member functions that do not depend on every template argument

