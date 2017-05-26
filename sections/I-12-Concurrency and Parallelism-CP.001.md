### <a name="Rconc-multi"></a>CP.1: Assume that your code will run as part of a multi-threaded program

##### Reason

It is hard to be certain that concurrency isn't used now or will be sometime in the future.
Code gets re-used.
Libraries using threads may be used from some other part of the program.
Note that this applies most urgently to library code and least urgently to stand-alone applications.
However, thanks to the magic of cut-and-paste, code fragments can turn up in unexpected places.

##### Example

```cpp
double cached_computation(double x)
{
    static double cached_x = 0.0;
    static double cached_result = COMPUTATION_OF_ZERO;
    double result;

    if (cached_x == x)
        return cached_result;
    result = computation(x);
    cached_x = x;
    cached_result = result;
    return result;
}

```
Although `cached_computation` works perfectly in a single-threaded environment, in a multi-threaded environment the two `static` variables result in data races and thus undefined behavior.

There are several ways that this example could be made safe for a multi-threaded environment:

* Delegate concurrency concerns upwards to the caller.
* Mark the `static` variables as `thread_local` (which might make caching less effective).
* Implement concurrency control, for example, protecting the two `static` variables with a `static` lock (which might reduce performance).
* Have the caller provide the memory to be used for the cache, thereby delegating both memory allocation and concurrency concerns upwards to the caller.
* Refuse to build and/or run in a multi-threaded environment.
* Provide two implementations, one which is used in single-threaded environments and another which is used in multi-threaded environments.

##### Exception

Code that is never run in a multi-threaded environment.

Be careful: there are many examples where code that was "known" to never run in a multi-threaded program
was run as part of a multi-threaded program. Often years later.
Typically, such programs lead to a painful effort to remove data races.
Therefore, code that is never intended to run in a multi-threaded environment should be clearly labeled as such and ideally come with compile or run-time enforcement mechanisms to catch those usage bugs early.

