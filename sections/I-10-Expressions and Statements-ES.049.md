### <a name="Res-casts-named"></a>ES.49: If you must use a cast, use a named cast

##### Reason

Readability. Error avoidance.
Named casts are more specific than a C-style or functional cast, allowing the compiler to catch some errors.

The named casts are:

* `static_cast`
* `const_cast`
* `reinterpret_cast`
* `dynamic_cast`
* `std::move`         // `move(x)` is an rvalue reference to `x`
* `std::forward`      // `forward(x)` is an rvalue reference to `x`
* `gsl::narrow_cast`  // `narrow_cast<T>(x)` is `static_cast<T>(x)`
* `gsl::narrow`       // `narrow<T>(x)` is `static_cast<T>(x)` if `static_cast<T>(x) == x` or it throws `narrowing_error`

##### Example

```cpp
class B { /* ... */ };
class D { /* ... */ };

template<typename D> D* upcast(B* pb)
{
    D* pd0 = pb;                        // error: no implicit conversion from B* to D*
    D* pd1 = (D*)pb;                    // legal, but what is done?
    D* pd2 = static_cast<D*>(pb);       // error: D is not derived from B
    D* pd3 = reinterpret_cast<D*>(pb);  // OK: on your head be it!
    D* pd4 = dynamic_cast<D*>(pb);      // OK: return nullptr
    // ...
}

```
The example was synthesized from real-world bugs where `D` used to be derived from `B`, but someone refactored the hierarchy.
The C-style cast is dangerous because it can do any kind of conversion, depriving us of any protection from mistakes (now or in the future).

##### Note

When converting between types with no information loss (e.g. from `float` to
`double` or `int64` from `int32`), brace initialization may be used instead.

```cpp
double d {some_float};
int64_t i {some_int32};

```
This makes it clear that the type conversion was intended and also prevents
conversions between types that might result in loss of precision. (It is a
compilation error to try to initialize a `float` from a `double` in this fashion,
for example.)

##### Note

`reinterpret_cast` can be essential, but the essential uses (e.g., turning a machine address into pointer) are not type safe:

```cpp
auto p = reinterpret_cast<Device_register>(0x800);  // inherently dangerous


```
##### Enforcement

* Flag C-style and functional casts.
* The [type profile](I-22-Profiles.md#Pro-type-reinterpretcast) bans `reinterpret_cast`.

