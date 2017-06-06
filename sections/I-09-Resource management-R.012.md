### <a name="Rr-immediate-alloc"></a>R.12: Immediately give the result of an explicit resource allocation to a manager object

##### Reason

If you don't, an exception or a return may lead to a leak.

##### Example, bad

```cpp
void f(const string& name)
{
    FILE* f = fopen(name, "r");          // open the file
    vector<char> buf(1024);
    auto _ = finally([f] { fclose(f); })  // remember to close the file
    // ...
}

```
The allocation of `buf` may fail and leak the file handle.

##### Example

```cpp
void f(const string& name)
{
    ifstream f{name};   // open the file
    vector<char> buf(1024);
    // ...
}

```
The use of the file handle (in `ifstream`) is simple, efficient, and safe.

##### Enforcement

* Flag explicit allocations used to initialize pointers (problem: how many direct resource allocations can we recognize?)

