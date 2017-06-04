### <a name="Res-while-for"></a>ES.73: Prefer a `while`-statement to a `for`-statement when there is no obvious loop variable

##### Reason

Readability.

##### Example

    int events = 0;
    for (; wait_for_event(); ++events) {  // bad, confusing
        // ...
    }

The "event loop" is misleading because the `events` counter has nothing to do with the loop condition (`wait_for_event()`).
Better

    int events = 0;
    while (wait_for_event()) {      // better
        ++events;
        // ...
    }

##### Enforcement

Flag actions in `for`-initializers and `for`-increments that do not relate to the `for`-condition.

