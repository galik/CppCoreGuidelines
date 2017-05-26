### <a name="Rp-library"></a>P.11: Encapsulate messy constructs, rather than spreading through the code

##### Reason

Messy code is more likely to hide bugs and harder to write.
A good interface is easier and safer to use.
Messy, low-level code breeds more such code.

##### Example

```cpp
int sz = 100;
int* p = (int*) malloc(sizeof(int) * sz);
int count = 0;
// ...
for (;;) {
    // ... read an int into x, exit loop if end of file is reached ...
    // ... check that x is valid ...
    if (count == sz)
        p = (int*) realloc(p, sizeof(int) * sz * 2);
    p[count++] = x;
    // ...
}

```
This is low-level, verbose, and error-prone.
For example, we "forgot" to test for memory exhaustion.
Instead, we could use `vector`:

```cpp
vector<int> v;
v.reserve(100);
// ...
for (int x; cin >> x; ) {
    // ... check that x is valid ...
    v.push_back(x);
}

```
##### Note

The standards library and the GSL are examples of this philosophy.
For example, instead of messing with the arrays, unions, cast, tricky lifetime issues, `gsl::owner`, etc.
that are needed to implement key abstractions, such as `vector`, `span`, `lock_guard`, and `future`, we use the libraries
designed and implemented by people with more time and expertise than we usually have.
Similarly, we can and should design and implement more specialized libraries, rather than leaving the users (often ourselves)
with the challenge of repeatedly getting low-level code well.
This is a variant of the [subset of superset principle](I-02-Introduction-In.000.md#R0) that underlies these guidelines.

##### Enforcement

* Look for "messy code" such as complex pointer manipulation and casting outside the implementation of abstractions.


