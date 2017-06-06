### <a name="Rf-capture-vs-overload"></a>F.50: Use a lambda when a function won't do (to capture local variables, or to write a local function)

##### Reason

Functions can't capture local variables or be declared at local scope; if you need those things, prefer a lambda where possible, and a handwritten function object where not. On the other hand, lambdas and function objects don't overload; if you need to overload, prefer a function (the workarounds to make lambdas overload are ornate). If either will work, prefer writing a function; use the simplest tool necessary.

##### Example

```cpp
// writing a function that should only take an int or a string
// -- overloading is natural
void f(int);
void f(const string&);

// writing a function object that needs to capture local state and appear
// at statement or expression scope -- a lambda is natural
vector<work> v = lots_of_work();
for (int tasknum = 0; tasknum < max; ++tasknum) {
    pool.run([=, &v]{
        /*
        ...
        ... process 1 / max - th of v, the tasknum - th chunk
        ...
        */
    });
}
pool.join();

```
##### Exception

Generic lambdas offer a concise way to write function templates and so can be useful even when a normal function template would do equally well with a little more syntax. This advantage will probably disappear in the future once all functions gain the ability to have Concept parameters.

##### Enforcement

* Warn on use of a named non-generic lambda (e.g., `auto x = [](int i){ /*...*/; };`) that captures nothing and appears at global scope. Write an ordinary function instead.

