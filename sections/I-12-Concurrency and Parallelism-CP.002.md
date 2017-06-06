### <a name="Rconc-races"></a>CP.2: Avoid data races

##### Reason

Unless you do, nothing is guaranteed to work and subtle errors will persist.

##### Note

In a nutshell, if two threads can access the same object concurrently (without synchronization), and at least one is a writer (performing a non-`const` operation), you have a data race.
For further information of how to use synchronization well to eliminate data races, please consult a good book about concurrency.

##### Example, bad

There are many examples of data races that exist, some of which are running in
production software at this very moment. One very simple example:

```cpp
int get_id() {
  static int id = 1;
  return id++;
}

```
The increment here is an example of a data race. This can go wrong in many ways,
including:

* Thread A loads the value of `id`, the OS context switches A out for some
  period, during which other threads create hundreds of IDs. Thread A is then
  allowed to run again, and `id` is written back to that location as A's read of
  `id` plus one.
* Thread A and B load `id` and increment it simultaneously.  They both get the
  same ID.

Local static variables are a common source of data races.

##### Example, bad:

```cpp
void f(fstream&  fs, regex pat)
{
    array<double, max> buf;
    int sz = read_vec(fs, buf, max);            // read from fs into buf
    gsl::span<double> s {buf};
    // ...
    auto h1 = async([&]{ sort(par, s); });     // spawn a task to sort
    // ...
    auto h2 = async([&]{ return find_all(buf, sz, pat); });   // span a task to find matches
    // ...
}

```
Here, we have a (nasty) data race on the elements of `buf` (`sort` will both read and write).
All data races are nasty.
Here, we managed to get a data race on data on the stack.
Not all data races are as easy to spot as this one.

##### Example, bad:

```cpp
// code not controlled by a lock

unsigned val;

if (val < 5) {
    // ... other thread can change val here ...
    switch (val) {
    case 0: // ...
    case 1: // ...
    case 2: // ...
    case 3: // ...
    case 4: // ...
    }
}

```
Now, a compiler that does not know that `val` can change will  most likely implement that `switch` using a jump table with five entries.
Then, a `val` outside the `[0..4]` range will cause a jump to an address that could be anywhere in the program, and execution would proceed there.
Really, "all bets are off" if you get a data race.
Actually, it can be worse still: by looking at the generated code you may be able to determine where the stray jump will go for a given value;
this can be a security risk.

##### Enforcement

Some is possible, do at least something.
There are commercial and open-source tools that try to address this problem,
but be aware that solutions have costs and blind spots.
Static tools often have many false positives and run-time tools often have a significant cost.
We hope for better tools.
Using multiple tools can catch more problems than a single one.

There are other ways you can mitigate the chance of data races:

* Avoid global data
* Avoid `static` variables
* More use of value types on the stack (and don't pass pointers around too much)
* More use of immutable data (literals, `constexpr`, and `const`)

