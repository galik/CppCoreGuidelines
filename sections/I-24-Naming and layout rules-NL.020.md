### <a name="Rl-stmt"></a>NL.20: Don't place two statements on the same line

##### Reason

Readability.
It is really easy to overlook a statement when there is more on a line.

##### Example

    int x = 7; char* p = 29;    // don't
    int x = 7; f(x);  ++x;      // don't

##### Enforcement

Easy.

