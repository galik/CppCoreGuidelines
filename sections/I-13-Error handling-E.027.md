### <a name="Re-no-throw-codes"></a>E.27: If you can't throw exceptions, use error codes systematically

##### Reason

Systematic use of any error-handling strategy minimizes the chance of forgetting to handle an error.

See also [Simulating RAII](I-13-Error%20handling-E.025.md#Re-no-throw-raii).

##### Note

There are several issues to be addressed:

* how do you transmit an error indicator from out of a function?
* how do you release all resources from a function before doing an error exit?
* What do you use as an error indicator?

In general, returning an error indicator implies returning two values: The result and an error indicator.
The error indicator can be part of the object, e.g. an object can have a `valid()` indicator
or a pair of values can be returned.

##### Example

```cpp
Gadget make_gadget(int n)
{
    // ...
}

void user()
{
    Gadget g = make_gadget(17);
    if (!g.valid()) {
            // error handling
    }
    // ...
}

```
This approach fits with [simulated RAII resource management](I-13-Error%20handling-E.025.md#Re-no-throw-raii).
The `valid()` function could return an `error_indicator` (e.g. a member of an `error_indicator` enumeration).

##### Example

What if we cannot or do not want to modify the `Gadget` type?
In that case, we must return a pair of values.
For example:

```cpp
std::pair<Gadget, error_indicator> make_gadget(int n)
{
    // ...
}

void user()
{
    auto r = make_gadget(17);
    if (!r.second) {
            // error handling
    }
    Gadget& g = r.first;
    // ...
}

```
As shown, `std::pair` is a possible return type.
Some people prefer a specific type.
For example:

```cpp
Gval make_gadget(int n)
{
    // ...
}

void user()
{
    auto r = make_gadget(17);
    if (!r.err) {
            // error handling
    }
    Gadget& g = r.val;
    // ...
}

```
One reason to prefer a specific return type is to have names for its members, rather than the somewhat cryptic `first` and `second`
and to avoid confusion with other uses of `std::pair`.

##### Example

In general, you must clean up before an error exit.
This can be messy:

```cpp
std::pair<int, error_indicator> user()
{
    Gadget g1 = make_gadget(17);
    if (!g1.valid()) {
            return {0, g1_error};
    }

    Gadget g2 = make_gadget(17);
    if (!g2.valid()) {
            cleanup(g1);
            return {0, g2_error};
    }

    // ...

    if (all_foobar(g1, g2)) {
        cleanup(g1);
        cleanup(g2);
        return {0, foobar_error};
    // ...

    cleanup(g1);
    cleanup(g2);
    return {res, 0};
}

```
Simulating RAII can be non-trivial, especially in functions with multiple resources and multiple possible errors.
A not uncommon technique is to gather cleanup at the end of the function to avoid repetition:

```cpp
std::pair<int, error_indicator> user()
{
    error_indicator err = 0;

    Gadget g1 = make_gadget(17);
    if (!g1.valid()) {
            err = g1_error;
            goto exit;
    }

    Gadget g2 = make_gadget(17);
    if (!g2.valid()) {
            err = g2_error;
            goto exit;
    }

    if (all_foobar(g1, g2)) {
        err = foobar_error;
        goto exit;
    }
    // ...

exit:
  if (g1.valid()) cleanup(g1);
  if (g2.valid()) cleanup(g2);
  return {res, err};
}

```
The larger the function, the more tempting this technique becomes.
`finally` can [ease the pain a bit](I-13-Error%20handling-E.019.md#Re-finally).
Also, the larger the program becomes the harder it is to apply an error-indicator-based error handling strategy systematically.

We [prefer exception-based error handling](I-13-Error%20handling-E.002.md#Re-throw) and recommend [keeping functions short](I-05-Functions-F.003.md#Rf-single).

**See also**: [Discussion](#Sd-???).

**See also**: [Returning multiple values](I-05-Functions-F.021.md#Rf-out-multi).

##### Enforcement

Awkward.

