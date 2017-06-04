### <a name="Rs-cycles"></a>SF.9: Avoid cyclic dependencies among source files

##### Reason

Cycles complicates comprehension and slows down compilation.
Complicates conversion to use language-supported modules (when they become available).

##### Note

Eliminate cycles; don't just break them with `#include` guards.

##### Example, bad

    // file1.h:
    #include "file2.h"

    // file2.h:
    #include "file3.h"

    // file3.h:
    #include "file1.h"

##### Enforcement

Flag all cycles.


