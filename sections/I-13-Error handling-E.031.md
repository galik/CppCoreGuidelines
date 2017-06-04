### <a name="Re_catch"></a>E.31: Properly order your `catch`-clauses

##### Reason

`catch`-clauses are evaluated in the order they appear and one clause can hide another.

##### Example

    void f()
    {
        // ...
        try {
                // ...
        }
        catch (Base& b) { /* ... */ }
        catch (Derived& d) { /* ... */ }
        catch (...) { /* ... */ }
        catch (std::exception& e){ /* ... */ }
    }

If `Derived`is derived from `Base` the `Derived`-handler will never be invoked.
The "catch everything" handler ensured that the `std::exception`-handler will never be invoked.

##### Enforcement

Flag all "hiding handlers".

