### <a name="Rf-package"></a>F.1: "Package" meaningful operations as carefully named functions

##### Reason

Factoring out common code makes code more readable, more likely to be reused, and limit errors from complex code.
If something is a well-specified action, separate it out from its surrounding code and give it a name.

##### Example, don't

```cpp
void read_and_print(istream& is)    // read and print an int
{
    int x;
    if (is >> x)
        cout << "the int is " << x << '\n';
    else
        cerr << "no int on input\n";
}

```
Almost everything is wrong with `read_and_print`.
It reads, it writes (to a fixed `ostream`), it writes error messages (to a fixed `ostream`), it handles only `int`s.
There is nothing to reuse, logically separate operations are intermingled and local variables are in scope after the end of their logical use.
For a tiny example, this looks OK, but if the input operation, the output operation, and the error handling had been more complicated the tangled
mess could become hard to understand.

##### Note

If you write a non-trivial lambda that potentially can be used in more than one place, give it a name by assigning it to a (usually non-local) variable.

##### Example

```cpp
sort(a, b, [](T x, T y) { return x.rank() < y.rank() && x.value() < y.value(); });

```
Naming that lambda breaks up the expression into its logical parts and provides a strong hint to the meaning of the lambda.

```cpp
auto lessT = [](T x, T y) { return x.rank() < y.rank() && x.value() < y.value(); };

sort(a, b, lessT);
find_if(a, b, lessT);

```
The shortest code is not always the best for performance or maintainability.

##### Exception

Loop bodies, including lambdas used as loop bodies, rarely need to be named.
However, large loop bodies (e.g., dozens of lines or dozens of pages) can be a problem.
The rule [Keep functions short](I-05-Functions-F.003.md#Rf-single) implies "Keep loop bodies short."
Similarly, lambdas used as callback arguments are sometimes non-trivial, yet unlikely to be re-usable.

##### Enforcement

* See [Keep functions short](I-05-Functions-F.003.md#Rf-single)
* Flag identical and very similar lambdas used in different places.

