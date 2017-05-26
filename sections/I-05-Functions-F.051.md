### <a name="Rf-default-args"></a>F.51: Where there is a choice, prefer default arguments over overloading

##### Reason

Default arguments simply provides alternative interfaces to a single implementation.
There is no guarantee that a set of overloaded functions all implement the same semantics.
The use of default arguments can avoid code replication.

##### Note

There is a choice between using default argument and overloading when the alternatives are from a set of arguments of the same types.
For example:

```cpp
void print(const string& s, format f = {});

```
as opposed to

```cpp
void print(const string& s);  // use default format
void print(const string& s, format f);

```
There is not a choice when a set of functions are used to do a semantically equivalent operation to a set of types. For example:

```cpp
void print(const char&);
void print(int);
void print(zstring);

```
##### See also


[Default arguments for virtual functions](I-07-Constructors, assignments, and destructors-C.139.md#Rh-virtual-default-arg)

##### Enforcement

```cpp
???

```
