### <a name="Res-macros2"></a>ES.31: Don't use macros for constants or "functions"

##### Reason

Macros are a major source of bugs.
Macros don't obey the usual scope and type rules.
Macros don't obey the usual rules for argument passing.
Macros ensure that the human reader sees something different from what the compiler sees.
Macros complicate tool building.

##### Example, bad

```cpp
#define PI 3.14
#define SQUARE(a, b) (a * b)

```
Even if we hadn't left a well-known bug in `SQUARE` there are much better behaved alternatives; for example:

```cpp
constexpr double pi = 3.14;
template<typename T> T square(T a, T b) { return a * b; }

```
##### Enforcement

Scream when you see a macro that isn't just used for source control (e.g., `#ifdef`)

