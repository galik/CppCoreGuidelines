### <a name="Res-casts"></a>ES.48: Avoid casts

##### Reason

Casts are a well-known source of errors. Make some optimizations unreliable.

##### Example, bad

```cpp
double d = 2;
auto p = (long*)&d;
auto q = (long long*)&d;
cout << d << ' ' << *p << ' ' << *q << '\n';

```
What would you think this fragment prints? The result is at best implementation defined. I got

```cpp
2 0 4611686018427387904

```
Adding

```cpp
*q = 666;
cout << d << ' ' << *p << ' ' << *q << '\n';

```
I got

```cpp
3.29048e-321 666 666

```
Surprised? I'm just glad I didn't crash the program.

##### Note

Programmer who write casts typically assumes that they know what they are doing.
In fact, they often disable the general rules for using values.
Overload resolution and template instantiation usually pick the right function if there is a right function to pick.
If there is not, maybe there ought to be, rather than applying a local fix (cast).

##### Note

Casts are necessary in a systems programming language.  For example, how else
would we get the address of a device register into a pointer?  However, casts
are seriously overused as well as a major source of errors.

##### Note

If you feel the need for a lot of casts, there may be a fundamental design problem.

##### Alternatives

Casts are widely (mis) used. Modern C++ has constructs that eliminate the need for casts in many contexts, such as

* Use templates
* Use `std::variant`


##### Enforcement

* Force the elimination of C-style casts
* Warn against named casts
* Warn if there are many functional style casts (there is an obvious problem in quantifying 'many').
* The [type profile](I-22-Profiles.md#Pro-type-reinterpretcast) bans `reinterpret_cast`.

