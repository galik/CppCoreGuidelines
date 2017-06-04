### <a name="Rconst-immutable"></a>Con.1: By default, make objects immutable

##### Reason

Immutable objects are easier to reason about, so make objects non-`const` only when there is a need to change their value.
Prevents accidental or hard-to-notice change of value.

##### Example

    for (const int i : c) cout << i << '\n';    // just reading: const

    for (int i : c) cout << i << '\n';          // BAD: just reading

##### Exception

Function arguments are rarely mutated, but also rarely declared const.
To avoid confusion and lots of false positives, don't enforce this rule for function arguments.

    void f(const char* const p); // pedantic
    void g(const int i);        // pedantic

Note that function parameter is a local variable so changes to it are local.

##### Enforcement

* Flag non-const variables that are not modified (except for parameters to avoid many false positives)

