### <a name="Rp-mutable"></a>P.10: Prefer immutable data to mutable data

##### Reason

It is easier to reason about constants than about variables.
Something immutable cannot change unexpectedly.
Sometimes immutability enables better optimization.
You can't have a data race on a constant.

See [Con: Constants and Immutability](I-14-Constants and Immutability.md#S-const)

