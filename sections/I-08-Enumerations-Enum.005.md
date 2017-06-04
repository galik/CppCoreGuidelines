### <a name="Renum-caps"></a>Enum.5: Don't use `ALL_CAPS` for enumerators

##### Reason

Avoid clashes with macros.

##### Example, bad

     // webcolors.h (third party header)
    #define RED   0xFF0000
    #define GREEN 0x00FF00
    #define BLUE  0x0000FF

    // productinfo.h
    // The following define product subtypes based on color

    enum class Product_info { RED, PURPLE, BLUE };   // syntax error

##### Enforcement

Flag ALL_CAPS enumerators.

