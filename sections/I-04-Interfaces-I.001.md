### <a name="Ri-explicit"></a>I.1: Make interfaces explicit

##### Reason

Correctness. Assumptions not stated in an interface are easily overlooked and hard to test.

##### Example, bad

Controlling the behavior of a function through a global (namespace scope) variable (a call mode) is implicit and potentially confusing. For example:

```cpp
int rnd(double d)
{
    return (rnd_up) ? ceil(d) : d;    // don't: "invisible" dependency
}

```
It will not be obvious to a caller that the meaning of two calls of `rnd(7.2)` might give different results.

##### Exception

Sometimes we control the details of a set of operations by an environment variable, e.g., normal vs. verbose output or debug vs. optimized.
The use of a non-local control is potentially confusing, but controls only implementation details of otherwise fixed semantics.

##### Example, bad

Reporting through non-local variables (e.g., `errno`) is easily ignored. For example:

```cpp
// don't: no test of printf's return value
fprintf(connection, "logging: %d %d %d\n", x, y, s);

```
What if the connection goes down so that no logging output is produced? See I.??.

**Alternative**: Throw an exception. An exception cannot be ignored.

**Alternative formulation**: Avoid passing information across an interface through non-local or implicit state.
Note that non-`const` member functions pass information to other member functions through their object's state.

**Alternative formulation**: An interface should be a function or a set of functions.
Functions can be template functions and sets of functions can be classes or class templates.

##### Enforcement

* (Simple) A function should not make control-flow decisions based on the values of variables declared at namespace scope.
* (Simple) A function should not write to variables declared at namespace scope.

