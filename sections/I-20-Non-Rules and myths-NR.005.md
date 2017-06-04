### <a name="Rnr-two-phase-init"></a>NR.5: Don't: Don't do substantive work in a constructor; instead use two-phase initialization

##### Reason (not to follow this rule)

Following this rule leads to weaker invariants,
more complicated code (having to deal with semi-constructed objects),
and errors (when we didn't deal correctly with semi-constructed objects consistently).

##### Example

    ???

##### Alternative

* Always establish a class invariant in a constructor.
* Don't define an object before it is needed.

