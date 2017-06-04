### <a name="Rs-include-order"></a>SF.4: Include `.h` files before other declarations in a file

##### Reason

Minimize context dependencies and increase readability.

##### Example

    #include <vector>
    #include <algorithm>
    #include <string>

    // ... my code here ...

##### Example, bad

    #include <vector>

    // ... my code here ...

    #include <algorithm>
    #include <string>

##### Note

This applies to both `.h` and `.cpp` files.

##### Note

There is an argument for insulating code from declarations and macros in header files by `#including` headers *after* the code we want to protect
(as in the example labeled "bad").
However

* that only works for one file (at one level): Use that technique in a header included with other headers and the vulnerability reappears.
* a namespace (an "implementation namespace") can protect against many context dependencies.
* full protection and flexibility require [modules](http://www.open-std.org/jtc1/sc22/wg21/docs/papers/2016/n4592.pdf).
[See also](http://www.open-std.org/jtc1/sc22/wg21/docs/papers/2016/p0141r0.pdf).


##### Enforcement

Easy.

