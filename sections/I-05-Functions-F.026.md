### <a name="Rf-unique_ptr"></a>F.26: Use a `unique_ptr<T>` to transfer ownership where a pointer is needed

##### Reason

Using `unique_ptr` is the cheapest way to pass a pointer safely.

See also [C.50](I-07-Constructors%2C%20assignments%2C%20and%20destructors-C.050.md#Rc-factory) regarding when to return a `shared_ptr` from a factory.

##### Example

```cpp
unique_ptr<Shape> get_shape(istream& is)  // assemble shape from input stream
{
    auto kind = read_header(is); // read header and identify the next shape on input
    switch (kind) {
    case kCircle:
        return make_unique<Circle>(is);
    case kTriangle:
        return make_unique<Triangle>(is);
    // ...
    }
}

```
##### Note

You need to pass a pointer rather than an object if what you are transferring is an object from a class hierarchy that is to be used through an interface (base class).

##### Enforcement

(Simple) Warn if a function returns a locally-allocated raw pointer. Suggest using either `unique_ptr` or `shared_ptr` instead.

