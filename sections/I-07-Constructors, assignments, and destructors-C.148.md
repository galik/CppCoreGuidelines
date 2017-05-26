### <a name="Rh-ptr-cast"></a>C.148: Use `dynamic_cast` to a pointer type when failure to find the required class is considered a valid alternative

##### Reason

The `dynamic_cast` conversion allows to test whether a pointer is pointing at a polymorphic object that has a given class in its hierarchy. Since failure to find the class merely returns a null value, it can be tested during run-time. This allows writing code that can choose alternative paths depending on the results.

Contrast with [C.147](I-07-Constructors, assignments, and destructors-C.148.md#Rh-ptr-cast), where failure is an error, and should not be used for conditional execution.

##### Example

The example below describes the `add` method of a `Shape_owner` that takes ownership of constructed `Shape` objects. The objects are also sorted into views, according to their geometric attributes.
In this example, `Shape` does not inherit from `Geometric_attributes`. Only its subclasses do.

```cpp
void add(Shape* const item)
{
  // Ownership is always taken
  owned_shapes.emplace_back(item);

  // Check the Geometric_attributes and add the shape to none/one/some/all of the views

  if (auto even = dynamic_cast<Even_sided*>(item))
  {
    view_of_evens.emplace_back(even);
  }

  if (auto trisym = dynamic_cast<Trilaterally_symmetrical*>(item))
  {
    view_of_trisyms.emplace_back(trisym);
  }
}

```
##### Notes

A failure to find the required class will cause `dynamic_cast` to return a null value, and de-referencing a null-valued pointer will lead to undefined behavior.
Therefore the result of the `dynamic_cast` should always be treated as if it may contain a null value, and tested.

##### Enforcement

* (Complex) Unless there is a null test on the result of a `dynamic_cast` of a pointer type, warn upon dereference of the pointer.

