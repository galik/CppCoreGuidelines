### <a name="Rh-poly"></a>C.145: Access polymorphic objects through pointers and references

##### Reason

If you have a class with a virtual function, you don't (in general) know which class provided the function to be used.

##### Example

```cpp
struct B { int a; virtual int f(); };
struct D : B { int b; int f() override; };

void use(B b)
{
    D d;
    B b2 = d;   // slice
    B b3 = b;
}

void use2()
{
    D d;
    use(d);   // slice
}

```
Both `d`s are sliced.

##### Exception

You can safely access a named polymorphic object in the scope of its definition, just don't slice it.

```cpp
void use3()
{
    D d;
    d.f();   // OK
}

```
##### Enforcement

Flag all slicing.

