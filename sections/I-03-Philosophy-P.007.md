### <a name="Rp-early"></a>P.7: Catch run-time errors early

##### Reason

Avoid "mysterious" crashes.
Avoid errors leading to (possibly unrecognized) wrong results.

##### Example

```cpp
void increment1(int* p, int n)    // bad: error prone
{
    for (int i = 0; i < n; ++i) ++p[i];
}

void use1(int m)
{
    const int n = 10;
    int a[n] = {};
    // ...
    increment1(a, m);   // maybe typo, maybe m <= n is supposed
                        // but assume that m == 20
    // ...
}

```
Here we made a small error in `use1` that will lead to corrupted data or a crash.
The (pointer, count)-style interface leaves `increment1()` with no realistic way of defending itself against out-of-range errors.
If we could check subscripts for out of range access, then the error would not be discovered until `p[10]` was accessed.
We could check earlier and improve the code:

```cpp
void increment2(span<int> p)
{
    for (int& x : p) ++x;
}

void use2(int m)
{
    const int n = 10;
    int a[n] = {};
    // ...
    increment2({a, m});    // maybe typo, maybe m <= n is supposed
    // ...
}

```
Now, `m <= n` can be checked at the point of call (early) rather than later.
If all we had was a typo so that we meant to use `n` as the bound, the code could be further simplified (eliminating the possibility of an error):

```cpp
void use3(int m)
{
    const int n = 10;
    int a[n] = {};
    // ...
    increment2(a);   // the number of elements of a need not be repeated
    // ...
}

```
##### Example, bad

Don't repeatedly check the same value. Don't pass structured data as strings:

```cpp
Date read_date(istream& is);    // read date from istream

Date extract_date(const string& s);    // extract date from string

void user1(const string& date)    // manipulate date
{
    auto d = extract_date(date);
    // ...
}

void user2()
{
    Date d = read_date(cin);
    // ...
    user1(d.to_string());
    // ...
}

```
The date is validated twice (by the `Date` constructor) and passed as a character string (unstructured data).

##### Example

Excess checking can be costly.
There are cases where checking early is dumb because you may not ever need the value, or may only need part of the value that is more easily checked than the whole.  Similarly, don't add validity checks that change the asymptotic behavior of your interface (e.g., don't add a `O(n)` check to an interface with an average complexity of `O(1)`).

```cpp
class Jet {    // Physics says: e * e < x * x + y * y + z * z
    float x;
    float y;
    float z;
    float e;
public:
    Jet(float x, float y, float z, float e)
        :x(x), y(y), z(z), e(e)
    {
        // Should I check here that the values are physically meaningful?
    }

    float m() const
    {
        // Should I handle the degenerate case here?
        return sqrt(x * x + y * y + z * z - e * e);
    }

    ???
};

```
The physical law for a jet (`e * e < x * x + y * y + z * z`) is not an invariant because of the possibility for measurement errors.

???

##### Enforcement

* Look at pointers and arrays: Do range-checking early and not repeatedly
* Look at conversions: Eliminate or mark narrowing conversions
* Look for unchecked values coming from input
* Look for structured data (objects of classes with invariants) being converted into strings
* ???

