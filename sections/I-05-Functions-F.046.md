### <a name="Rf-main"></a>F.46: `int` is the return type for `main()`

##### Reason

It's a language rule, but violated through "language extensions" so often that it is worth mentioning.
Declaring `main` (the one global `main` of a program) `void` limits portability.

##### Example

        void main() { /* ... */ };  // bad, not C++

        int main()
        {
            std::cout << "This is the way to do it\n";
        }

##### Note

We mention this only because of the persistence of this error in the community.

##### Enforcement

* The compiler should do it
* If the compiler doesn't do it, let tools flag it

