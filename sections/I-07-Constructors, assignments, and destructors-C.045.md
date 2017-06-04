### <a name="Rc-default"></a>C.45: Don't define a default constructor that only initializes data members; use in-class member initializers instead

##### Reason

Using in-class member initializers lets the compiler generate the function for you. The compiler-generated function can be more efficient.

##### Example, bad

    class X1 { // BAD: doesn't use member initializers
        string s;
        int i;
    public:
        X1() :s{"default"}, i{1} { }
        // ...
    };

##### Example

    class X2 {
        string s = "default";
        int i = 1;
    public:
        // use compiler-generated default constructor
        // ...
    };

##### Enforcement

(Simple) A default constructor should do more than just initialize member variables with constants.

