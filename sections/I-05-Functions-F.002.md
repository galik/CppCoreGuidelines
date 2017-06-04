### <a name="Rf-logical"></a>F.2: A function should perform a single logical operation

##### Reason

A function that performs a single operation is simpler to understand, test, and reuse.

##### Example

Consider:

    void read_and_print()    // bad
    {
        int x;
        cin >> x;
        // check for errors
        cout << x << "\n";
    }

This is a monolith that is tied to a specific input and will never find another (different) use. Instead, break functions up into suitable logical parts and parameterize:

    int read(istream& is)    // better
    {
        int x;
        is >> x;
        // check for errors
        return x;
    }

    void print(ostream& os, int x)
    {
        os << x << "\n";
    }

These can now be combined where needed:

    void read_and_print()
    {
        auto x = read(cin);
        print(cout, x);
    }

If there was a need, we could further templatize `read()` and `print()` on the data type, the I/O mechanism, the response to errors, etc. Example:

    auto read = [](auto& input, auto& value)    // better
    {
        input >> value;
        // check for errors
    };

    auto print(auto& output, const auto& value)
    {
        output << value << "\n";
    }

##### Enforcement

* Consider functions with more than one "out" parameter suspicious. Use return values instead, including `tuple` for multiple return values.
* Consider "large" functions that don't fit on one editor screen suspicious. Consider factoring such a function into smaller well-named suboperations.
* Consider functions with 7 or more parameters suspicious.

