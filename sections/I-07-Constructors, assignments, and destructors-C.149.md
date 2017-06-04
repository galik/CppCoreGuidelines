### <a name="Rh-smart"></a>C.149: Use `unique_ptr` or `shared_ptr` to avoid forgetting to `delete` objects created using `new`

##### Reason

Avoid resource leaks.

##### Example

    void use(int i)
    {
        auto p = new int {7};           // bad: initialize local pointers with new
        auto q = make_unique<int>(9);   // ok: guarantee the release of the memory allocated for 9
        if (0 < i) return;              // maybe return and leak
        delete p;                       // too late
    }

##### Enforcement

* Flag initialization of a naked pointer with the result of a `new`
* Flag `delete` of local variable

