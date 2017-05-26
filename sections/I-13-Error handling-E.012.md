### <a name="Re-noexcept"></a>E.12: Use `noexcept` when exiting a function because of a `throw` is impossible or unacceptable

##### Reason

To make error handling systematic, robust, and efficient.

##### Example

```cpp
double compute(double d) noexcept
{
    return log(sqrt(d <= 0 ? 1 : d));
}

```
Here, we know that `compute` will not throw because it is composed out of operations that don't throw.
By declaring `compute` to be `noexcept`, we give the compiler and human readers information that can make it easier for them to understand and manipulate `compute`.

##### Note

Many standard library functions are `noexcept` including all the standard library functions "inherited" from the C standard library.

##### Example

```cpp
vector<double> munge(const vector<double>& v) noexcept
{
    vector<double> v2(v.size());
    // ... do something ...
}

```
The `noexcept` here states that I am not willing or able to handle the situation where I cannot construct the local `vector`.
That is, I consider memory exhaustion a serious design error (on par with hardware failures) so that I'm willing to crash the program if it happens.

##### Note

Do not use traditional [exception-specifications](I-13-Error%20handling-E.030.md#Re-specifications).

##### See also

[discussion](I-28-Discussion-Discussion.md#Sd-noexcept).

