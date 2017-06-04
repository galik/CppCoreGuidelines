### <a name="Res-ellipses"></a> ES.34: Don't define a (C-style) variadic function

##### Reason

Not type safe.
Requires messy cast-and-macro-laden code to get working right.

##### Example

    #include <cstdarg>

    // "severity" followed by a zero-terminated list of char*s; write the C-style strings to cerr
    void error(int severity ...)
    {
        va_list ap;             // a magic type for holding arguments
        va_start(ap, severity); // arg startup: "severity" is the first argument of error()

        for (;;) {
            // treat the next var as a char*; no checking: a cast in disguise
            char* p = va_arg(ap, char*);
            if (p == nullptr) break;
            cerr << p << ' ';
        }

        va_end(ap);             // arg cleanup (don't forget this)

        cerr << '\n';
        if (severity) exit(severity);
    }

    void use()
    {
        error(7, "this", "is", "an", "error", nullptr);
        error(7); // crash
        error(7, "this", "is", "an", "error");  // crash
        const char* is = "is";
        string an = "an";
        error(7, "this", "is", an, "error"); // crash
    }

**Alternative**: Overloading. Templates. Variadic templates.

##### Note

This is basically the way `printf` is implemented.

##### Enforcement

* Flag definitions of C-style variadic functions.
* Flag `#include <cstdarg>` and `#include <stdarg.h>`


## ES.stmt: Statements

Statements control the flow of control (except for function calls and exception throws, which are expressions).

