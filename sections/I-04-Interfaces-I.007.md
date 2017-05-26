### <a name="Ri-post"></a>I.7: State postconditions

##### Reason

To detect misunderstandings about the result and possibly catch erroneous implementations.

##### Example, bad

Consider:

```cpp
int area(int height, int width) { return height * width; }  // bad

```
Here, we (incautiously) left out the precondition specification, so it is not explicit that height and width must be positive.
We also left out the postcondition specification, so it is not obvious that the algorithm (`height * width`) is wrong for areas larger than the largest integer.
Overflow can happen.
Consider using:

```cpp
int area(int height, int width)
{
    auto res = height * width;
    Ensures(res > 0);
    return res;
}

```
##### Example, bad

Consider a famous security bug:

```cpp
void f()    // problematic
{
    char buffer[MAX];
    // ...
    memset(buffer, 0, MAX);
}

```
There was no postcondition stating that the buffer should be cleared and the optimizer eliminated the apparently redundant `memset()` call:

```cpp
void f()    // better
{
    char buffer[MAX];
    // ...
    memset(buffer, 0, MAX);
    Ensures(buffer[0] == 0);
}

```
##### Note

Postconditions are often informally stated in a comment that states the purpose of a function; `Ensures()` can be used to make this more systematic, visible, and checkable.

##### Note

Postconditions are especially important when they relate to something that is not directly reflected in a returned result, such as a state of a data structure used.

##### Example

Consider a function that manipulates a `Record`, using a `mutex` to avoid race conditions:

```cpp
mutex m;

void manipulate(Record& r)    // don't
{
    m.lock();
    // ... no m.unlock() ...
}

```
Here, we "forgot" to state that the `mutex` should be released, so we don't know if the failure to ensure release of the `mutex` was a bug or a feature.
Stating the postcondition would have made it clear:

```cpp
void manipulate(Record& r)    // postcondition: m is unlocked upon exit
{
    m.lock();
    // ... no m.unlock() ...
}

```
The bug is now obvious (but only to a human reading comments).

Better still, use [RAII](I-09-Resource%20management-R.001.md#Rr-raii) to ensure that the postcondition ("the lock must be released") is enforced in code:

```cpp
void manipulate(Record& r)    // best
{
    lock_guard<mutex> _ {m};
    // ...
}

```
##### Note

Ideally, postconditions are stated in the interface/declaration so that users can easily see them.
Only postconditions related to the users can be stated in the interface.
Postconditions related only to internal state belongs in the definition/implementation.

##### Enforcement

(Not enforceable) This is a philosophical guideline that is infeasible to check
directly in the general case. Domain specific checkers (like lock-holding
checkers) exist for many toolchains.

