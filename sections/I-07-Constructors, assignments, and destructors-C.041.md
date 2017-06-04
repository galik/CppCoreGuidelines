### <a name="Rc-complete"></a>C.41: A constructor should create a fully initialized object

##### Reason

A constructor establishes the invariant for a class. A user of a class should be able to assume that a constructed object is usable.

##### Example, bad

    class X1 {
        FILE* f;   // call init() before any other function
        // ...
    public:
        X1() {}
        void init();   // initialize f
        void read();   // read from f
        // ...
    };

    void f()
    {
        X1 file;
        file.read();   // crash or bad read!
        // ...
        file.init();   // too late
        // ...
    }

Compilers do not read comments.

##### Exception

If a valid object cannot conveniently be constructed by a constructor, [use a factory function](I-07-Constructors%2C%20assignments%2C%20and%20destructors-C.050.md#Rc-factory).

##### Enforcement

* (Simple) Every constructor should initialize every member variable (either explicitly, via a delegating ctor call or via default construction).
* (Unknown) If a constructor has an `Ensures` contract, try to see if it holds as a postcondition.

##### Note

If a constructor acquires a resource (to create a valid object), that resource should be [released by the destructor](I-07-Constructors%2C%20assignments%2C%20and%20destructors-C.031.md#Rc-dtor-release).
The idiom of having constructors acquire resources and destructors release them is called [RAII](I-09-Resource%20management-R.001.md#Rr-raii) ("Resource Acquisition Is Initialization").

