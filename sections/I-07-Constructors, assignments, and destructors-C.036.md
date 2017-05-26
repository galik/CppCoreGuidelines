### <a name="Rc-dtor-fail"></a>C.36: A destructor may not fail

##### Reason

In general we do not know how to write error-free code if a destructor should fail.
The standard library requires that all classes it deals with have destructors that do not exit by throwing.

##### Example

```cpp
class X {
public:
    ~X() noexcept;
    // ...
};

X::~X() noexcept
{
    // ...
    if (cannot_release_a_resource) terminate();
    // ...
}

```
##### Note

Many have tried to devise a fool-proof scheme for dealing with failure in destructors.
None have succeeded to come up with a general scheme.
This can be a real practical problem: For example, what about a socket that won't close?
The writer of a destructor does not know why the destructor is called and cannot "refuse to act" by throwing an exception.
See [discussion](I-28-Discussion-Discussion.md#Sd-dtor).
To make the problem worse, many "close/release" operations are not retryable.
If at all possible, consider failure to close/cleanup a fundamental design error and terminate.

##### Note

Declare a destructor `noexcept`. That will ensure that it either completes normally or terminate the program.

##### Note

If a resource cannot be released and the program may not fail, try to signal the failure to the rest of the system somehow
(maybe even by modifying some global state and hope something will notice and be able to take care of the problem).
Be fully aware that this technique is special-purpose and error-prone.
Consider the "my connection will not close" example.
Probably there is a problem at the other end of the connection and only a piece of code responsible for both ends of the connection can properly handle the problem.
The destructor could send a message (somehow) to the responsible part of the system, consider that to have closed the connection, and return normally.

##### Note

If a destructor uses operations that may fail, it can catch exceptions and in some cases still complete successfully
(e.g., by using a different clean-up mechanism from the one that threw an exception).

##### Enforcement

(Simple) A destructor should be declared `noexcept` if it could throw.

