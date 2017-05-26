### <a name="Re-never-throw"></a>E.13: Never throw while being the direct owner of an object

##### Reason

That would be a leak.

##### Example

```cpp
void leak(int x)   // don't: may leak
{
    auto p = new int{7};
    if (x < 0) throw Get_me_out_of_here{};  // may leak *p
    // ...
    delete p;   // we may never get here
}

```
One way of avoiding such problems is to use resource handles consistently:

```cpp
void no_leak(int x)
{
    auto p = make_unique<int>(7);
    if (x < 0) throw Get_me_out_of_here{};  // will delete *p if necessary
    // ...
    // no need for delete p
}

```
Another solution (often better) would be to use a local variable to eliminate explicit use of pointers:

```cpp
void no_leak_simplified(int x)
{
    vector<int> v(7);
    // ...
}

```
##### Note

If you have local "things" that requires cleanup, but is not represented by an object with a destructor, such cleanup must
also be done before a `throw`.
Sometimes, [`finally()`](I-13-Error handling-E.019.md#Re-finally) can make such unsystematic cleanup a bit more manageable.

