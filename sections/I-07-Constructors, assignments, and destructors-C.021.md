### <a name="Rc-five"></a>C.21: If you define or `=delete` any default operation, define or `=delete` them all

##### Reason

The semantics of the special functions are closely related, so if one needs to be non-default, the odds are that others need modification too.

##### Example, bad

    struct M2 {   // bad: incomplete set of default operations
    public:
        // ...
        // ... no copy or move operations ...
        ~M2() { delete[] rep; }
    private:
        pair<int, int>* rep;  // zero-terminated set of pairs
    };

    void use()
    {
        M2 x;
        M2 y;
        // ...
        x = y;   // the default assignment
        // ...
    }

Given that "special attention" was needed for the destructor (here, to deallocate), the likelihood that copy and move assignment (both will implicitly destroy an object) are correct is low (here, we would get double deletion).

##### Note

This is known as "the rule of five" or "the rule of six", depending on whether you count the default constructor.

##### Note

If you want a default implementation of a default operation (while defining another), write `=default` to show you're doing so intentionally for that function.
If you don't want a default operation, suppress it with `=delete`.

##### Note

Compilers enforce much of this rule and ideally warn about any violation.

##### Note

Relying on an implicitly generated copy operation in a class with a destructor is deprecated.

##### Enforcement

(Simple) A class should have a declaration (even a `=delete` one) for either all or none of the special functions.

