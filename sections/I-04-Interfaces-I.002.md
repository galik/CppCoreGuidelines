### <a name="Ri-global"></a>I.2: Avoid global variables

##### Reason

Non-`const` global variables hide dependencies and make the dependencies subject to unpredictable changes.

##### Example

    struct Data {
        // ... lots of stuff ...
    } data;            // non-const data

    void compute()     // don't
    {
        // ... use data ...
    }

    void output()     // don't
    {
        // ... use data ...
    }

Who else might modify `data`?

##### Note

Global constants are useful.

##### Note

The rule against global variables applies to namespace scope variables as well.

**Alternative**: If you use global (more generally namespace scope) data to avoid copying, consider passing the data as an object by reference to `const`.
Another solution is to define the data as the state of some object and the operations as member functions.

**Warning**: Beware of data races: If one thread can access nonlocal data (or data passed by reference) while another thread executes the callee, we can have a data race.
Every pointer or reference to mutable data is a potential data race.

##### Note

You cannot have a race condition on immutable data.

**References**: See the [rules for calling functions](I-05-Functions-F.009.md#SS-call).

##### Enforcement

(Simple) Report all non-`const` variables declared at namespace scope.

