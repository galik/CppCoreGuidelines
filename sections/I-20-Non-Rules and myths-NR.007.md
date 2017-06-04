### <a name="Rnr-protected-data"></a>NR.7: Don't: Make all data members `protected`

##### Reason (not to follow this rule)

`protected` data is a source of errors.
`protected` data can be manipulated from an unbounded amount of code in various places.
`protected` data is the class hierarchy equivalent to global data.

##### Example

    ???

##### Alternative

* [Make member data `public` or (preferably) `private`](I-07-Constructors%2C%20assignments%2C%20and%20destructors-C.133.md#Rh-protected)


