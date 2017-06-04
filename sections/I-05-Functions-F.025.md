### <a name="Rf-zstring"></a>F.25: Use a `zstring` or a `not_null<zstring>` to designate a C-style string

##### Reason

C-style strings are ubiquitous. They are defined by convention: zero-terminated arrays of characters.
We must distinguish C-style strings from a pointer to a single character or an old-fashioned pointer to an array of characters.

##### Example

Consider:

    int length(const char* p);

When I call `length(s)` should I test for `s == nullptr` first? Should the implementation of `length()` test for `p == nullptr`?

    // the implementor of length() must assume that p == nullptr is possible
    int length(zstring p);

    // it is the caller's job to make sure p != nullptr
    int length(not_null<zstring> p);

##### Note

`zstring` do not represent ownership.

**See also**: [Support library](I-23-Guideline%20support%20library.md#S-gsl).

