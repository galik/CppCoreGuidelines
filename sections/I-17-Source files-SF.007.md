### <a name="Rs-using-directive"></a>SF.7: Don't write `using namespace` in a header file

##### Reason

Doing so takes away an `#include`r's ability to effectively disambiguate and to use alternatives.

##### Example

    // bad.h
    #include <iostream>
    using namespace std; // bad

    // user.cpp
    #include "bad.h"
    
    bool copy(/*... some parameters ...*/);    // some function that happens to be named copy

    int main() {
        copy(/*...*/);    // now overloads local ::copy and std::copy, could be ambiguous
    }

##### Enforcement

Flag `using namespace` at global scope in a header file.

