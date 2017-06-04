### <a name="Rc-dtor-ref"></a>C.34: If a class has an owning reference member, define a destructor

##### Reason

A reference member may represent a resource.
It should not do so, but in older code, that's common.
See [pointer members and destructors](I-07-Constructors%2C%20assignments%2C%20and%20destructors-C.032.md#Rc-dtor-ptr).
Also, copying may lead to slicing.

##### Example, bad

    class Handle {  // Very suspect
        Shape& s;   // use reference rather than pointer to prevent rebinding
                    // BAD: vague about ownership of *p
        // ...
    public:
        Handle(Shape& ss) : s{ss} { /* ... */ }
        // ...
    };

The problem of whether `Handle` is responsible for the destruction of its `Shape` is the same as for [the pointer case](I-07-Constructors%2C%20assignments%2C%20and%20destructors-C.032.md#Rc-dtor-ptr):
If the `Handle` owns the object referred to by `s` it must have a destructor.

##### Example

    class Handle {        // OK
        owner<Shape&> s;  // use reference rather than pointer to prevent rebinding
        // ...
    public:
        Handle(Shape& ss) : s{ss} { /* ... */ }
        ~Handle() { delete &s; }
        // ...
    };

Independently of whether `Handle` owns its `Shape`, we must consider the default copy operations suspect:

    // the Handle had better own the Circle or we have a leak
    Handle x {*new Circle{p1, 17}};

    Handle y {*new Triangle{p1, p2, p3}};
    x = y;     // the default assignment will try *x.s = *y.s

That `x = y` is highly suspect.
Assigning a `Triangle` to a `Circle`?
Unless `Shape` has its [copy assignment `=deleted`](I-07-Constructors%2C%20assignments%2C%20and%20destructors-C.067.md#Rc-copy-virtual), only the `Shape` part of `Triangle` is copied into the `Circle`.

##### Note

Why not just require all owning references to be replaced by "smart pointers"?
Changing from references to smart pointers implies code changes.
We don't (yet) have smart references.
Also, that may affect ABIs.

##### Enforcement

* A class with a reference data member is suspect.
* A class with an `owner<T>` reference should define its default operations.

