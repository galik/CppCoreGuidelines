### <a name="Rr-newdelete"></a>R.11: Avoid calling `new` and `delete` explicitly

##### Reason

The pointer returned by `new` should belong to a resource handle (that can call `delete`).
If the pointer returned by `new` is assigned to a plain/naked pointer, the object can be leaked.

##### Note

In a large program, a naked `delete` (that is a `delete` in application code, rather than part of code devoted to resource management)
is a likely bug: if you have N `delete`s, how can you be certain that you don't need N+1 or N-1?
The bug may be latent: it may emerge only during maintenance.
If you have a naked `new`, you probably need a naked `delete` somewhere, so you probably have a bug.

##### Enforcement

(Simple) Warn on any explicit use of `new` and `delete`. Suggest using `make_unique` instead.

