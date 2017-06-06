### <a name="Rp-what"></a>P.3: Express intent

##### Reason

Unless the intent of some code is stated (e.g., in names or comments), it is impossible to tell whether the code does what it is supposed to do.

##### Example

```cpp
int i = 0;
while (i < v.size()) {
    // ... do something with v[i] ...
}

```
The intent of "just" looping over the elements of `v` is not expressed here. The implementation detail of an index is exposed (so that it might be misused), and `i` outlives the scope of the loop, which may or may not be intended. The reader cannot know from just this section of code.

Better:

```cpp
for (const auto& x : v) { /* do something with the value of x */ }

```
Now, there is no explicit mention of the iteration mechanism, and the loop operates on a reference to `const` elements so that accidental modification cannot happen. If modification is desired, say so:

```cpp
for (auto& x : v) { /* modify x */ }

```
Sometimes better still, use a named algorithm:

```cpp
for_each(v, [](int x) { /* do something with the value of x */ });
for_each(par, v, [](int x) { /* do something with the value of x */ });

```
The last variant makes it clear that we are not interested in the order in which the elements of `v` are handled.

A programmer should be familiar with

* [The guideline support library](I-23-Guideline%20support%20library.md#S-gsl)
* [The ISO C++ standard library](I-18-The%20Standard%20Library.md#S-stdlib)
* Whatever foundation libraries are used for the current project(s)

##### Note

Alternative formulation: Say what should be done, rather than just how it should be done.

##### Note

Some language constructs express intent better than others.

##### Example

If two `int`s are meant to be the coordinates of a 2D point, say so:

```cpp
draw_line(int, int, int, int);  // obscure
draw_line(Point, Point);        // clearer

```
##### Enforcement

Look for common patterns for which there are better alternatives

* simple `for` loops vs. range-`for` loops
* `f(T*, int)` interfaces vs. `f(span<T>)` interfaces
* loop variables in too large a scope
* naked `new` and `delete`
* functions with many parameters of built-in types

There is a huge scope for cleverness and semi-automated program transformation.

