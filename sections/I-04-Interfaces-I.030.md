### <a name="Ri-encapsulate"></a>I.30: Encapsulate rule violations

##### Reason

To keep code simple and safe.
Sometimes, ugly, unsafe, or error-prone techniques are necessary for logical or performance reasons.
If so, keep them local, rather than "infecting" interfaces so that larger groups of programmers have to be aware of the
subtleties.
Implementation complexity should, if at all possible, not leak through interfaces into user code.

##### Example

Consider a program that, depending on some form of input (e.g., arguments to `main`), should consume input
from a file, from the command line, or from standard input.
We might write

```cpp
bool owned;
owner<istream*> inp;
switch (source) {
case std_in:        owned = false; inp = &cin;
case command_line:  owned = true;  inp = new istringstream{argv[2]};
case file:          owned = true;  inp = new ifstream{argv[2]};
}
istream& in = *inp;

```
This violated the rule [against uninitialized variables](I-10-Expressions and Statements-ES.020.md#Res-always),
the rule against [ignoring ownership](I-04-Interfaces-I.011.md#Ri-raw),
and the rule [against magic constants](I-10-Expressions and Statements-ES.045.md#Res-magic) .
In particular, someone has to remember to somewhere write

```cpp
if (owned) delete inp;

```
We could handle this particular example by using `unique_ptr` with a special deleter that does nothing for `cin`,
but that's complicated for novices (who can easily encounter this problem) and the example is an example of a more general
problem where a property that we would like to consider static (here, ownership) needs infrequently be addressed
at run time.
The common, most frequent, and safest examples can be handled statically, so we don't want to add cost and complexity to those.
But we must also cope with the uncommon, less-safe, and necessarily more expensive cases.
Such examples are discussed in [[Str15]](http://www.stroustrup.com/resource-model.pdf).

So, we write a class

```cpp
class Istream { [[gsl::suppress(lifetime)]]
public:
    enum Opt { from_line = 1 };
    Istream() { }
    Istream(zstring p) :owned{true}, inp{new ifstream{p}} {}            // read from file
    Istream(zstring p, Opt) :owned{true}, inp{new istringstream{p}} {}  // read from command line
    ~Itream() { if (owned) delete inp; }
    operator istream& () { return *inp; }
private:
    bool owned = false;
    istream* inp = &cin;
};

```
Now, the dynamic nature of `istream` ownership has been encapsulated.
Presumably, a bit of checking for potential errors would be added in real code.

##### Enforcement

* Hard, it is hard to decide what rule-breaking code is essential
* flag rule suppression that enable rule-violations to cross interfaces

