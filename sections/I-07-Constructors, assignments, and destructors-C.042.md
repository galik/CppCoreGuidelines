### <a name="Rc-throw"></a>C.42: If a constructor cannot construct a valid object, throw an exception

##### Reason

Leaving behind an invalid object is asking for trouble.

##### Example

    class X2 {
        FILE* f;   // call init() before any other function
        // ...
    public:
        X2(const string& name)
            :f{fopen(name.c_str(), "r")}
        {
            if (f == nullptr) throw runtime_error{"could not open" + name};
            // ...
        }

        void read();      // read from f
        // ...
    };

    void f()
    {
        X2 file {"Zeno"}; // throws if file isn't open
        file.read();      // fine
        // ...
    }

##### Example, bad

    class X3 {     // bad: the constructor leaves a non-valid object behind
        FILE* f;   // call init() before any other function
        bool valid;
        // ...
    public:
        X3(const string& name)
            :f{fopen(name.c_str(), "r")}, valid{false}
        {
            if (f) valid = true;
            // ...
        }

        bool is_valid() { return valid; }
        void read();   // read from f
        // ...
    };

    void f()
    {
        X3 file {"Heraclides"};
        file.read();   // crash or bad read!
        // ...
        if (file.is_valid()) {
            file.read();
            // ...
        }
        else {
            // ... handle error ...
        }
        // ...
    }

##### Note

For a variable definition (e.g., on the stack or as a member of another object) there is no explicit function call from which an error code could be returned.
Leaving behind an invalid object and relying on users to consistently check an `is_valid()` function before use is tedious, error-prone, and inefficient.

##### Exception

There are domains, such as some hard-real-time systems (think airplane controls) where (without additional tool support) exception handling is not sufficiently predictable from a timing perspective.
There the `is_valid()` technique must be used. In such cases, check `is_valid()` consistently and immediately to simulate [RAII](I-09-Resource%20management-R.001.md#Rr-raii).

##### Alternative

If you feel tempted to use some "post-constructor initialization" or "two-stage initialization" idiom, try not to do that.
If you really have to, look at [factory functions](I-07-Constructors%2C%20assignments%2C%20and%20destructors-C.050.md#Rc-factory).

##### Note

One reason people have used `init()` functions rather than doing the initialization work in a constructor has been to avoid code replication.
[Delegating constructors](I-07-Constructors%2C%20assignments%2C%20and%20destructors-C.051.md#Rc-delegating) and [default member initialization](I-07-Constructors%2C%20assignments%2C%20and%20destructors-C.048.md#Rc-in-class-initializer) do that better.
Another reason is been to delay initialization until an object is needed; the solution to that is often [not to declare a variable until it can be properly initialized](I-10-Expressions%20and%20Statements-ES.022.md#Res-init)

##### Enforcement

???

