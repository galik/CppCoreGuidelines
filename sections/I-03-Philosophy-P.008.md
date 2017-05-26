### <a name="Rp-leak"></a>P.8: Don't leak any resources

##### Reason

Even a slow growth in resources will, over time, exhaust the availability of those resources.
This is particularly important for long-running programs, but is an essential piece of responsible programming behavior.

##### Example, bad

```cpp
void f(char* name)
{
    FILE* input = fopen(name, "r");
    // ...
    if (something) return;   // bad: if something == true, a file handle is leaked
    // ...
    fclose(input);
}

```
Prefer [RAII](I-09-Resource%20management-R.001.md#Rr-raii):

```cpp
void f(char* name)
{
    ifstream input {name};
    // ...
    if (something) return;   // OK: no leak
    // ...
}

```
**See also**: [The resource management section](I-09-Resource%20management.md#S-resource)

##### Note

A leak is colloquially "anything that isn't cleaned up."
The more important classification is "anything that can no longer be cleaned up."
For example, allocating an object on the heap and then losing the last pointer that points to that allocation.
This rule should not be taken as requiring that allocations within long-lived objects must be returned during program shutdown.
For example, relying on system guaranteed cleanup such as file closing and memory deallocation upon process shutdown can simplify code.
However, relying on abstractions that implicitly clean up can be as simple, and often safer.

##### Note

Enforcing [the lifetime profile](#In.force) eliminates leaks.
When combined with resource safety provided by [RAII](I-09-Resource%20management-R.001.md#Rr-raii), it eliminates the need for "garbage collection" (by generating no garbage).
Combine this with enforcement of [the type and bounds profiles](#In.force) and you get complete type- and resource-safety, guaranteed by tools.

##### Enforcement

* Look at pointers: Classify them into non-owners (the default) and owners.
  Where feasible, replace owners with standard-library resource handles (as in the example above).
  Alternatively, mark an owner as such using `owner` from [the GSL](I-23-Guideline%20support%20library.md#S-gsl).
* Look for naked `new` and `delete`
* Look for known resource allocating functions returning raw pointers (such as `fopen`, `malloc`, and `strdup`)

