### <a name="Rf-this-capture"></a>F.54: If you capture `this`, capture all variables explicitly (no default capture)

##### Reason

It's confusing. Writing `[=]` in a member function appears to capture by value, but actually captures data members by reference because it actually captures the invisible `this` pointer by value. If you meant to do that, write `this` explicitly.

##### Example

```cpp
class My_class {
    int x = 0;
    // ...

    void f() {
        int i = 0;
        // ...

        auto lambda = [=]{ use(i, x); };   // BAD: "looks like" copy/value capture
        // [&] has identical semantics and copies the this pointer under the current rules
        // [=,this] and [&,this] are not much better, and confusing

        x = 42;
        lambda(); // calls use(42);
        x = 43;
        lambda(); // calls use(43);

        // ...

        auto lambda2 = [i, this]{ use(i, x); }; // ok, most explicit and least confusing

        // ...
    }
};

```
##### Note

This is under active discussion in standardization, and may be addressed in a future version of the standard by adding a new capture mode or possibly adjusting the meaning of `[=]`. For now, just be explicit.

##### Enforcement

* Flag any lambda capture-list that specifies a default capture and also captures `this` (whether explicitly or via default capture)

