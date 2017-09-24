**Class Equivalents**

In order to increase the type safety of systems according to guidelines like [I.4](https://github.com/isocpp/CppCoreGuidelines/blob/master/CppCoreGuidelines.md#Ri-typed) from the [CppCoreGuidelines](https://github.com/isocpp/CppCoreGuidelines/blob/master/CppCoreGuidelines.md).

Currently if we want to make a typename more meaningful to aid readability we can us a type alias like so:

```cpp
using redlist = std::vector<int>;
using bluelist = std::vector<int>;
```

However this does not provide any additional type safety. We can still use a `std::vector<int>` wherever we ask for a `redlist` or a `bluelist` and, indeed we can use `redlist` and `bluelist` interchangeably. Sometimes this is exactly what we want. For example we sometimes make a type alias because the actual type is too long and unwieldy but it is the actual type we wish to accept. This is true of iterators, for example.

But other times we make type aliases to add meaning to the data the type contains. It may behave semantically identical to a *vector* of integers and yet require distinct treatment. We may want to avoid potential errors that might occur by accidentally sending a `std::vector<int>` to a function designed to process a `redlist`. We may want to protect ourselves from allowing a function designed to process `redlist` objects from receiving `bluelist` objects as a parameter. 

```cpp
using redlist = std::vector<int>;
using bluelist = std::vector<int>;

void process_reds(redlist const& reds)
{

}

void process_blues(bluelist const& blues)
{

}

// ...

redlist reds = get_latest_reds();
bluelist blues = get_old_blues();

process_reds(blues); // whoops error but compiler allows it
process_blues(reds); // whoops double dang but compiler allows it
```

This proposal would make it possible to define `redlist` and `bluelist` as *first class types* which share identical functionality with the type they were defined equal to but exist as separate and distinct entries in the compiler's type system.

The proposed syntax is to mirror the current `using` syntax when defining a type alias. So instead of this:

```cpp
using redlist = std::vector<int>;
using bluelist = std::vector<int>;
```

We can have this:

```cpp
class redlist = std::vector<int>;
class bluelist = std::vector<int>;
```

One class becomes *wholly equal* to another class.

So whereas the *type alias* syntax reads "using typename redlist is equal to using typename std::vector<int>", the proposed addition would read "class redlist is defined equal to (the same as) class std::vector<int>". It would literally be the same as redefining the entire class `std::vector<int>` but using the name `redlist` instead of `vector` (namespaces notwithstanding).

As this is a template class it would behave in all ways identical to the template `std::vector<T>` with `T == int` except the compiler would enforce type safety between `redlist`, `bluelist` and `vector<int>`. They could even share the same generated code.

Being first class types means that Class Equivalents could be overloaded. Whereas type aliases will cause an ambiguity here, Equivalent Classes will overload as if they were defined independently of the type they are equivalenced with.

```cpp
void process(redlist const& reds)
{

}

// redfinition with type aliases but legal overload with Class Equivalents 
void process(bluelist const& blues) 
{

}
```
There would be a natural explicit conversion using `static_cast` as in:
```cpp
redlist reds;
bluelist& blues = static_cast<bluelist&>(reds);
```

**Built in types**

It is also proposed that the concept be applied to built-in types too:

```cpp
class disk_id = int;
```

This would introduce a *strongly typed* integer that behaved *identically* to an actual *integer* except that it would *never* be convertible to an `int` without an explicit cast.

So now it becomes safe to write:

```cpp
void spin_down(disk_id id);
```

We can be sure no stray `int` will accidentally be sent to out disk function. We would have, in effect, created a new built-in numerical type that happens to behave identically to an `int` but that is non-interchangeable with `int` (except by explicit cast).





