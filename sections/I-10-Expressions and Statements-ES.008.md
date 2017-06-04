### <a name="Res-name-similar"></a>ES.8: Avoid similar-looking names

##### Reason

Code clarity and readability. Too-similar names slow down comprehension and increase the likelihood of error.

##### Example; bad

    if (readable(i1 + l1 + ol + o1 + o0 + ol + o1 + I0 + l0)) surprise();

##### Example; bad

Do not declare a non-type with the same name as a type in the same scope. This removes the need to disambiguate with a keyword such as `struct` or `enum`. It also removes a source of errors, as `struct X` can implicitly declare `X` if lookup fails.

    struct foo { int n; };
    struct foo foo();       // BAD, foo is a type already in scope
    struct foo x = foo();   // requires disambiguation

##### Exception

Antique header files might declare non-types and types with the same name in the same scope.

##### Enforcement

* Check names against a list of known confusing letter and digit combinations.
* Flag a declaration of a variable, function, or enumerator that hides a class or enumeration declared in the same scope.

