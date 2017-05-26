### <a name="Rf-consume"></a>F.18: For "consume" parameters, pass by `X&&` and `std::move` the parameter

##### Reason

It's efficient and eliminates bugs at the call site: `X&&` binds to rvalues, which requires an explicit `std::move` at the call site if passing an lvalue.

##### Example

```cpp
void sink(vector<int>&& v) {   // sink takes ownership of whatever the argument owned
    // usually there might be const accesses of v here
    store_somewhere(std::move(v));
    // usually no more use of v here; it is moved-from
}

```
Note that the `std::move(v)` makes it possible for `store_somewhere()` to leave `v` in a moved-from state.
[That could be dangerous](I-07-Constructors, assignments, and destructors-C.064.md#Rc-move-semantic).


##### Exception

Unique owner types that are move-only and cheap-to-move, such as `unique_ptr`, can also be passed by value which is simpler to write and achieves the same effect. Passing by value does generate one extra (cheap) move operation, but prefer simplicity and clarity first.

For example:

```cpp
template <class T>
void sink(std::unique_ptr<T> p) {
    // use p ... possibly std::move(p) onward somewhere else
}   // p gets destroyed

```
##### Enforcement

* Flag all `X&&` parameters (where `X` is not a template type parameter name) where the function body uses them without `std::move`.
* Flag access to moved-from objects.
* Don't conditionally move from objects

