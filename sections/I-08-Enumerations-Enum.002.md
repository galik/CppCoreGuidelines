### <a name="Renum-set"></a>Enum.2: Use enumerations to represent sets of related named constants

##### Reason

An enumeration shows the enumerators to be related and can be a named type.



##### Example

    enum class Web_color { red = 0xFF0000, green = 0x00FF00, blue = 0x0000FF };


##### Note

Switching on an enumeration is common and the compiler can warn against unusual patterns of case labels. For example:

    enum class Product_info { red = 0, purple = 1, blue = 2 };

    void print(Product_info inf)
    {
        switch (inf) {
        case Product_info::red: cout << "red"; break;
        case Product_info::purple: cout << "purple"; break;
        }
    }

Such off-by-one switch`statements are often the results of an added enumerator and insufficient testing.

##### Enforcement

* Flag `switch`-statements where the `case`s cover most but not all enumerators of an enumeration.
* Flag `switch`-statements where the `case`s cover a few enumerators of an enumeration, but has no `default`.


