### <a name="Renum-oper"></a>Enum.4: Define operations on enumerations for safe and simple use

##### Reason

Convenience of use and avoidance of errors.

##### Example

    enum class Day { mon, tue, wed, thu, fri, sat, sun };

    Day operator++(Day& d)
    {
        return d == Day::sun ? Day::mon : Day{++d};
    }

    Day today = Day::sat;
    Day tomorrow = ++today;

##### Enforcement

Flag repeated expressions cast back into an enumeration.


