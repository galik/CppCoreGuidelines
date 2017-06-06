### <a name="Rs-using"></a>SF.6: Use `using namespace` directives for transition, for foundation libraries (such as `std`), or within a local scope (only)

##### Reason

 `using namespace` can lead to name clashes, so it should be used sparingly.
 However, it is not always possible to qualify every name from a namespace in user code (e.g., during transition)
 and sometimes a namespace is so fundamental and prevalent in a code base, that consistent qualification would be verbose and distracting.

##### Example

```cpp
#include <string>
#include <vector>
#include <iostream>
#include <memory>
#include <algorithm>

using namespace std;

// ...

```
Here (obviously), the standard library is used pervasively and apparently no other library is used, so requiring `std::` everywhere
could be distracting.

##### Example

The use of `using namespace std;` leaves the programmer open to a name clash with a name from the standard library

```cpp
#include <cmath>
using namespace std;

int g(int x)
{
    int sqrt = 7;
    // ...
    return sqrt(x); // error
}

```
However, this is not particularly likely to lead to a resolution that is not an error and
people who use `using namespace std` are supposed to know about `std` and about this risk.

##### Note

A `.cpp` file is a form of local scope.
There is little difference in the opportunities for name clashes in an N-line `.cpp` containing a `using namespace X`,
an N-line function containing a `using namespace X`,
and M functions each containing a `using namespace X`with N lines of code in total.

##### Note

[Don't write `using namespace` in a header file](I-17-Source%20files-SF.007.md#Rs-using-directive).

##### Enforcement

Flag multiple `using namespace` directives for different namespaces in a single source file.

