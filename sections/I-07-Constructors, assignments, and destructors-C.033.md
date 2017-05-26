### <a name="Rc-dtor-ptr2"></a>C.33: If a class has an owning pointer member, define a destructor

##### Reason

An owned object must be `deleted` upon destruction of the object that owns it.

##### Example

A pointer member may represent a resource.
[A `T*` should not do so](I-09-Resource management-R.003.md#Rr-ptr), but in older code, that's common.
Consider a `T*` a possible owner and therefore suspect.

```cpp
template<typename T>
class Smart_ptr {
    T* p;   // BAD: vague about ownership of *p
    // ...
public:
    // ... no user-defined default operations ...
};

void use(Smart_ptr<int> p1)
{
    // error: p2.p leaked (if not nullptr and not owned by some other code)
    auto p2 = p1;
}

```
Note that if you define a destructor, you must define or delete [all default operations](I-07-Constructors, assignments, and destructors-C.021.md#Rc-five):

```cpp
template<typename T>
class Smart_ptr2 {
    T* p;   // BAD: vague about ownership of *p
    // ...
public:
    // ... no user-defined copy operations ...
    ~Smart_ptr2() { delete p; }  // p is an owner!
};

void use(Smart_ptr2<int> p1)
{
    auto p2 = p1;   // error: double deletion
}

```
The default copy operation will just copy the `p1.p` into `p2.p` leading to a double destruction of `p1.p`. Be explicit about ownership:

```cpp
template<typename T>
class Smart_ptr3 {
    owner<T*> p;   // OK: explicit about ownership of *p
    // ...
public:
    // ...
    // ... copy and move operations ...
    ~Smart_ptr3() { delete p; }
};

void use(Smart_ptr3<int> p1)
{
    auto p2 = p1;   // error: double deletion
}

```
##### Note

Often the simplest way to get a destructor is to replace the pointer with a smart pointer (e.g., `std::unique_ptr`) and let the compiler arrange for proper destruction to be done implicitly.

##### Note

Why not just require all owning pointers to be "smart pointers"?
That would sometimes require non-trivial code changes and may affect ABIs.

##### Enforcement

* A class with a pointer data member is suspect.
* A class with an `owner<T>` should define its default operations.

