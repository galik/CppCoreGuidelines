### <a name="Rf-single"></a>F.3: Keep functions short and simple

##### Reason

Large functions are hard to read, more likely to contain complex code, and more likely to have variables in larger than minimal scopes.
Functions with complex control structures are more likely to be long and more likely to hide logical errors

##### Example

Consider:

```cpp
double simpleFunc(double val, int flag1, int flag2)
    // simpleFunc: takes a value and calculates the expected ASIC output,
    // given the two mode flags.
{
    double intermediate;
    if (flag1 > 0) {
        intermediate = func1(val);
        if (flag2 % 2)
             intermediate = sqrt(intermediate);
    }
    else if (flag1 == -1) {
        intermediate = func1(-val);
        if (flag2 % 2)
             intermediate = sqrt(-intermediate);
        flag1 = -flag1;
    }
    if (abs(flag2) > 10) {
        intermediate = func2(intermediate);
    }
    switch (flag2 / 10) {
        case 1: if (flag1 == -1) return finalize(intermediate, 1.171);
                break;
        case 2: return finalize(intermediate, 13.1);
        default: break;
    }
    return finalize(intermediate, 0.);
}

```
This is too complex (and long).
How would you know if all possible alternatives have been correctly handled?
Yes, it breaks other rules also.

We can refactor:

```cpp
double func1_muon(double val, int flag)
{
    // ???
}

double funct1_tau(double val, int flag1, int flag2)
{
    // ???
}

double simpleFunc(double val, int flag1, int flag2)
    // simpleFunc: takes a value and calculates the expected ASIC output,
    // given the two mode flags.
{
    if (flag1 > 0)
        return func1_muon(val, flag2);
    if (flag1 == -1)
        // handled by func1_tau: flag1 = -flag1;
        return func1_tau(-val, flag1, flag2);
    return 0.;
}

```
##### Note

"It doesn't fit on a screen" is often a good practical definition of "far too large."
One-to-five-line functions should be considered normal.

##### Note

Break large functions up into smaller cohesive and named functions.
Small simple functions are easily inlined where the cost of a function call is significant.

##### Enforcement

* Flag functions that do not "fit on a screen."
  How big is a screen? Try 60 lines by 140 characters; that's roughly the maximum that's comfortable for a book page.
* Flag functions that are too complex. How complex is too complex?
  You could use cyclomatic complexity. Try "more than 10 logical path through." Count a simple switch as one path.

