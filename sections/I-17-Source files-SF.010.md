### <a name="Rs-implicit"></a>SF.10: Avoid dependencies on implicitly `#included` names

##### Reason

Avoid surprises.
Avoid having to change `#include`s if an `#include`d header changes.
Avoid accidentally becoming dependent on implementation details and logically separate entities included in a header.

##### Example

```cpp
#include <iostream>
using namespace std;

void use()                  // bad
{
    string s;
    cin >> s;               // fine
    getline(cin, s);        // error: getline() not defined
    if (s == "surprise") {  // error == not defined
        // ...
    }
}

```
<iostream> exposes the definition of `std::string` ("why?" makes for a fun trivia question),
but it is not required to do so by transitively including the entire `<string>` header,
resulting in the popular beginner question "why doesn't `getline(cin,s);` work?"
or even an occasional "`string`s cannot be compared with `==`).

The solution is to explicitly `#include<string>`:

```cpp
#include <iostream>
#include <string>
using namespace std;

void use()
{
    string s;
    cin >> s;               // fine
    getline(cin, s);        // fine
    if (s == "surprise") {  // fine
        // ...
    }
}

```
##### Note

Some headers exist exactly to collect a set of consistent declarations from a variety of headers.
For example:

```cpp
// basic_std_lib.h:

#include <vector>
#include <string>
#include <map>
#include <iostream>
#include <random>
#include <vector>

```
a user can now get that set of declarations with a single `#include`"

```cpp
#include "basic_std_lib.h"

```
This rule against implicit inclusion is not meant to prevent such deliberate aggregation.

##### Enforcement

Enforcement would require some knowledge about what in a header is meant to be "exported" to users and what is there to enable implementation.
No really good solution is possible until we have modules.

