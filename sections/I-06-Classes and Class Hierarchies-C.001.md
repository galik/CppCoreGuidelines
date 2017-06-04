### <a name="Rc-org"></a>C.1: Organize related data into structures (`struct`s or `class`es)

##### Reason

Ease of comprehension.
If data is related (for fundamental reasons), that fact should be reflected in code.

##### Example

    void draw(int x, int y, int x2, int y2);  // BAD: unnecessary implicit relationships
    void draw(Point from, Point to);          // better

##### Note

A simple class without virtual functions implies no space or time overhead.

##### Note

From a language perspective `class` and `struct` differ only in the default visibility of their members.

##### Enforcement

Probably impossible. Maybe a heuristic looking for data items used together is possible.

