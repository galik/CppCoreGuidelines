### <a name="Renum-underlying"></a>Enum.7: Specify the underlying type of an enumeration only when necessary

##### Reason

The default is the easiest to read and write.
`int` is the default integer type.
`int` is compatible with C `enum`s.

##### Example

    enum class Direction : char { n, s, e, w,
                                  ne, nw, se, sw };  // underlying type saves space

    enum class Web_color : int { red   = 0xFF0000,
                                 green = 0x00FF00,
                                 blue  = 0x0000FF };  // underlying type is redundant

##### Note

Specifying the underlying type is necessary in forward declarations of enumerations:

    enum Flags : char;

    void f(Flags);

    // ....

    enum flags : char { /* ... */ };


##### Enforcement

????


