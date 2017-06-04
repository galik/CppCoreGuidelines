### <a name="Rc-copy-virtual"></a>C.67: A base class should suppress copying, and provide a virtual `clone` instead if "copying" is desired

##### Reason

To prevent slicing, because the normal copy operations will copy only the base portion of a derived object.

##### Example, bad

    class B { // BAD: base class doesn't suppress copying
        int data;
        // ... nothing about copy operations, so uses default ...
    };

    class D : public B {
        string more_data; // add a data member
        // ...
    };

    auto d = make_unique<D>();

    // oops, slices the object; gets only d.data but drops d.more_data
    auto b = make_unique<B>(d);

##### Example

    class B { // GOOD: base class suppresses copying
        B(const B&) = delete;
        B& operator=(const B&) = delete;
        virtual unique_ptr<B> clone() { return /* B object */; }
        // ...
    };

    class D : public B {
        string more_data; // add a data member
        unique_ptr<B> clone() override { return /* D object */; }
        // ...
    };

    auto d = make_unique<D>();
    auto b = d.clone(); // ok, deep clone

##### Note

It's good to return a smart pointer, but unlike with raw pointers the return type cannot be covariant (for example, `D::clone` can't return a `unique_ptr<D>`. Don't let this tempt you into returning an owning raw pointer; this is a minor drawback compared to the major robustness benefit delivered by the owning smart pointer.

##### Exception

If you need covariant return types, return an `owner<derived*>`. See [C.130](I-07-Constructors%2C%20assignments%2C%20and%20destructors-C.130.md#Rh-copy).

##### Enforcement

A class with any virtual function should not have a copy constructor or copy assignment operator (compiler-generated or handwritten).

## C.other: Other default operation rules

In addition to the operations for which the language offer default implementations,
there are a few operations that are so foundational that it rules for their definition are needed:
comparisons, `swap`, and `hash`.

