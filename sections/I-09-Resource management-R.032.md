### <a name="Rr-uniqueptrparam"></a>R.32: Take a `unique_ptr<widget>` parameter to express that a function assumes ownership of a `widget`

##### Reason

Using `unique_ptr` in this way both documents and enforces the function call's ownership transfer.

##### Example

    void sink(unique_ptr<widget>); // consumes the widget

    void uses(widget*);            // just uses the widget

##### Example, bad

    void thinko(const unique_ptr<widget>&); // usually not what you want

##### Enforcement

* (Simple) Warn if a function takes a `Unique_ptr<T>` parameter by lvalue reference and does not either assign to it or call `reset()` on it on at least one code path. Suggest taking a `T*` or `T&` instead.
* (Simple) ((Foundation)) Warn if a function takes a `Unique_ptr<T>` parameter by reference to `const`. Suggest taking a `const T*` or `const T&` instead.

