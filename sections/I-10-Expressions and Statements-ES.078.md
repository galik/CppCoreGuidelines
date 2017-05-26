### <a name="Res-break"></a>ES.78: Always end a non-empty `case` with a `break`

##### Reason

 Accidentally leaving out a `break` is a fairly common bug.
 A deliberate fallthrough is a maintenance hazard.

##### Example

```cpp
switch (eventType)
{
case Information:
    update_status_bar();
    break;
case Warning:
    write_event_log();
case Error:
    display_error_window(); // Bad
    break;
}

```
It is easy to overlook the fallthrough. Be explicit:

```cpp
switch (eventType)
{
case Information:
    update_status_bar();
    break;
case Warning:
    write_event_log();
    // fallthrough
case Error:
    display_error_window(); // Bad
    break;
}

```
In C++17, use a `[[fallthrough]]` annotation:

```cpp
switch (eventType)
{
case Information:
    update_status_bar();
    break;
case Warning:
    write_event_log();
    [[fallthrough]];        // C++17
case Error:
    display_error_window(); // Bad
    break;
}

```
##### Note

Multiple case labels of a single statement is OK:

```cpp
switch (x) {
case 'a':
case 'b':
case 'f':
    do_something(x);
    break;
}

```
##### Enforcement

Flag all fallthroughs from non-empty `case`s.

