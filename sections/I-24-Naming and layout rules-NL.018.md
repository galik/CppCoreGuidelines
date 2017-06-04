### <a name="Rl-ptr"></a>NL.18: Use C++-style declarator layout

##### Reason

The C-style layout emphasizes use in expressions and grammar, whereas the C++-style emphasizes types.
The use in expressions argument doesn't hold for references.

##### Example

    T& operator[](size_t);   // OK
    T &operator[](size_t);   // just strange
    T & operator[](size_t);   // undecided

##### Enforcement

Impossible in the face of history.


