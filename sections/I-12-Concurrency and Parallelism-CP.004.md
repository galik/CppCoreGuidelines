### <a name="Rconc-task"></a>CP.4: Think in terms of tasks, rather than threads

##### Reason

A `thread` is an implementation concept, a way of thinking about the machine.
A task is an application notion, something you'd like to do, preferably concurrently with other tasks.
Application concepts are easier to reason about.

##### Example

```cpp
???

```
##### Note

With the exception of `async()`, the standard-library facilities are low-level, machine-oriented, threads-and-lock level.
This is a necessary foundation, but we have to try to raise the level of abstraction: for productivity, for reliability, and for performance.
This is a potent argument for using higher level, more applications-oriented libraries (if possibly, built on top of standard-library facilities).

##### Enforcement

???

