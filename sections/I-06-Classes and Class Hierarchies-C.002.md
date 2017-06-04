### <a name="Rc-struct"></a>C.2: Use `class` if the class has an invariant; use `struct` if the data members can vary independently

##### Reason

Readability.
Ease of comprehension.
The use of `class` alerts the programmer to the need for an invariant.
This is a useful convention.

##### Note

An invariant is a logical condition for the members of an object that a constructor must establish for the public member functions to assume.
After the invariant is established (typically by a constructor) every member function can be called for the object.
An invariant can be stated informally (e.g., in a comment) or more formally using `Expects`.

If all data members can vary independently of each other, no invariant is possible.

##### Example

    struct Pair {  // the members can vary independently
        string name;
        int volume;
    };

but:

    class Date {
    public:
        // validate that {yy, mm, dd} is a valid date and initialize
        Date(int yy, Month mm, char dd);
        // ...
    private:
        int y;
        Month m;
        char d;    // day
    };

##### Note

If a class has any `private` data, a user cannot completely initialize an object without the use of a constructor.
Hence, the class definer will provide a constructor and must specify its meaning.
This effectively means the definer need to define an invariant.

* See also [define a class with private data as `class`](I-06-Classes%20and%20Class%20Hierarchies-C.008.md#Rc-class).
* See also [Prefer to place the interface first in a class](I-24-Naming%20and%20layout%20rules-NL.016.md#Rl-order).
* See also [minimize exposure of members](I-06-Classes%20and%20Class%20Hierarchies-C.009.md#Rc-private).
* See also [Avoid `protected` data](I-07-Constructors%2C%20assignments%2C%20and%20destructors-C.133.md#Rh-protected).

##### Enforcement

Look for `struct`s with all data private and `class`es with public members.

