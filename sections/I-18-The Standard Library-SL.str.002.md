### <a name="Rstr-view"></a>SL.str.2: Use `std::string_view` or `gsl::string_span` to refer to character sequences

##### Reason

`std::string_view` or `gsl::string_span` provides simple and (potentially) safe access to character sequences independently of how
those sequences are allocated and stored.

##### Example

    vector<string> read_until(string_span terminator);

    void user(zstring p, const string& s, string_span ss)
    {
        auto v1 = read_until(p);
        auto v2 = read_until(s);
        auto v3 = read_until(ss);
        // ...
    }

##### Note

`std::string_view` (C++17) is read only.

##### Enforcement

???

