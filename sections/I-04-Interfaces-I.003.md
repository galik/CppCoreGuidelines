### <a name="Ri-singleton"></a>I.3: Avoid singletons

##### Reason

Singletons are basically complicated global objects in disguise.

##### Example

```cpp
class Singleton {
    // ... lots of stuff to ensure that only one Singleton object is created,
    // that it is initialized properly, etc.
};

```
There are many variants of the singleton idea.
That's part of the problem.

##### Note

If you don't want a global object to change, declare it `const` or `constexpr`.

##### Exception

You can use the simplest "singleton" (so simple that it is often not considered a singleton) to get initialization on first use, if any:

```cpp
X& myX()
{
    static X my_x {3};
    return my_x;
}

```
This is one of the most effective solutions to problems related to initialization order.
In a multi-threaded environment, the initialization of the static object does not introduce a race condition
(unless you carelessly access a shared object from within its constructor).

Note that the initialization of a local `static` does not imply a race condition.
However, if the destruction of `X` involves an operation that needs to be synchronized we must use a less simple solution.
For example:

```cpp
X& myX()
{
    static auto p = new X {3};
    return *p;  // potential leak
}

```
Now someone must `delete` that object in some suitably thread-safe way.
That's error-prone, so we don't use that technique unless

* `myX` is in multithreaded code,
* that `X` object needs to be destroyed (e.g., because it releases a resource), and
* `X`'s destructor's code needs to be synchronized.

If you, as many do, define a singleton as a class for which only one object is created, functions like `myX` are not singletons, and this useful technique is not an exception to the no-singleton rule.

##### Enforcement

Very hard in general.

* Look for classes with names that include `singleton`.
* Look for classes for which only a single object is created (by counting objects or by examining constructors).
* If a class X has a public static function that contains a function-local static of the class' type X and returns a pointer or reference to it, ban that.

