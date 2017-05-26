### <a name="Rp-direct"></a>P.1: Express ideas directly in code

##### Reason

Compilers don't read comments (or design documents) and neither do many programmers (consistently).
What is expressed in code has defined semantics and can (in principle) be checked by compilers and other tools.

##### Example

```cpp
class Date {
    // ...
public:
    Month month() const;  // do
    int month();          // don't
    // ...
};

```
The first declaration of `month` is explicit about returning a `Month` and about not modifying the state of the `Date` object.
The second version leaves the reader guessing and opens more possibilities for uncaught bugs.

##### Example

```cpp
void f(vector<string>& v)
{
    string val;
    cin >> val;
    // ...
    int index = -1;                    // bad
    for (int i = 0; i < v.size(); ++i)
        if (v[i] == val) {
            index = i;
            break;
        }
    // ...
}

```
That loop is a restricted form of `std::find`.
A much clearer expression of intent would be:

```cpp
void f(vector<string>& v)
{
    string val;
    cin >> val;
    // ...
    auto p = find(begin(v), end(v), val);  // better
    // ...
}

```
A well-designed library expresses intent (what is to be done, rather than just how something is being done) far better than direct use of language features.

A C++ programmer should know the basics of the standard library, and use it where appropriate.
Any programmer should know the basics of the foundation libraries of the project being worked on, and use them appropriately.
Any programmer using these guidelines should know the [guideline support library](I-23-Guideline%20support%20library.md#S-gsl), and use it appropriately.

##### Example

```cpp
change_speed(double s);   // bad: what does s signify?
// ...
change_speed(2.3);

```
A better approach is to be explicit about the meaning of the double (new speed or delta on old speed?) and the unit used:

```cpp
change_speed(Speed s);    // better: the meaning of s is specified
// ...
change_speed(2.3);        // error: no unit
change_speed(23m / 10s);  // meters per second

```
We could have accepted a plain (unit-less) `double` as a delta, but that would have been error-prone.
If we wanted both absolute speed and deltas, we would have defined a `Delta` type.

##### Enforcement

Very hard in general.

* use `const` consistently (check if member functions modify their object; check if functions modify arguments passed by pointer or reference)
* flag uses of casts (casts neuter the type system)
* detect code that mimics the standard library (hard)

