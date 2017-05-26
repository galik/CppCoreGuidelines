### <a name="Rf-return-ptr"></a>F.42: Return a `T*` to indicate a position (only)

##### Reason

That's what pointers are good for.
Returning a `T*` to transfer ownership is a misuse.

##### Example

```cpp
Node* find(Node* t, const string& s)  // find s in a binary tree of Nodes
{
    if (t == nullptr || t->name == s) return t;
    if ((auto p = find(t->left, s))) return p;
    if ((auto p = find(t->right, s))) return p;
    return nullptr;
}

```
If it isn't the `nullptr`, the pointer returned by `find` indicates a `Node` holding `s`.
Importantly, that does not imply a transfer of ownership of the pointed-to object to the caller.

##### Note

Positions can also be transferred by iterators, indices, and references.
A reference is often a superior alternative to a pointer [if there is no need to use `nullptr`](I-05-Functions-F.060.md#Rf-ptr-ref) or [if the object referred to should not change](???).

##### Note

Do not return a pointer to something that is not in the caller's scope; see [F.43](I-05-Functions-F.043.md#Rf-dangle).

**See also**: [discussion of dangling pointer prevention](#???).

##### Enforcement

* Flag `delete`, `std::free()`, etc. applied to a plain `T*`.
Only owners should be deleted.
* Flag `new`, `malloc()`, etc. assigned to a plain `T*`.
Only owners should be responsible for deletion.

