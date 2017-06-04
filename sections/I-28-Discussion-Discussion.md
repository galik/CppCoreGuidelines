### <a name="Sd-order"></a>Discussion: Define and initialize member variables in the order of member declaration

Member variables are always initialized in the order they are declared in the class definition, so write them in that order in the constructor initialization list. Writing them in a different order just makes the code confusing because it won't run in the order you see, and that can make it hard to see order-dependent bugs.

    class Employee {
        string email, first, last;
    public:
        Employee(const char* firstName, const char* lastName);
        // ...
    };

    Employee::Employee(const char* firstName, const char* lastName)
      : first(firstName),
        last(lastName),
        // BAD: first and last not yet constructed
        email(first + "." + last + "@acme.com")
    {}

In this example, `email` will be constructed before `first` and `last` because it is declared first. That means its constructor will attempt to use `first` and `last` too soon -- not just before they are set to the desired values, but before they are constructed at all.

If the class definition and the constructor body are in separate files, the long-distance influence that the order of member variable declarations has over the constructor's correctness will be even harder to spot.

**References**:

[\[Cline99\]](I-31-Bibliography.md#Cline99) §22.03-11, [\[Dewhurst03\]](Dewhurst03) §52-53, [\[Koenig97\]](I-31-Bibliography.md#Koenig97) §4, [\[Lakos96\]](I-31-Bibliography.md#Lakos96) §10.3.5, [\[Meyers97\]](I-31-Bibliography.md#Meyers97) §13, [\[Murray93\]](I-31-Bibliography.md#Murray93) §2.1.3, [\[Sutter00\]](I-31-Bibliography.md#Sutter00) §47

