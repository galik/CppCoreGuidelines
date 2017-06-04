### <a name="Rc-interface"></a>C.3: Represent the distinction between an interface and an implementation using a class

##### Reason

An explicit distinction between interface and implementation improves readability and simplifies maintenance.

##### Example

    class Date {
        // ... some representation ...
    public:
        Date();
        // validate that {yy, mm, dd} is a valid date and initialize
        Date(int yy, Month mm, char dd);

        int day() const;
        Month month() const;
        // ...
    };

For example, we can now change the representation of a `Date` without affecting its users (recompilation is likely, though).

##### Note

Using a class in this way to represent the distinction between interface and implementation is of course not the only way.
For example, we can use a set of declarations of freestanding functions in a namespace, an abstract base class, or a template function with concepts to represent an interface.
The most important issue is to explicitly distinguish between an interface and its implementation "details."
Ideally, and typically, an interface is far more stable than its implementation(s).

##### Enforcement

???

