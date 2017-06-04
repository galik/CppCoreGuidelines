### <a name="Ri-unrelated"></a>I.24: Avoid adjacent unrelated parameters of the same type

##### Reason

Adjacent arguments of the same type are easily swapped by mistake.

##### Example, bad

Consider:

```cpp
void copy_n(T* p, T* q, int n);  // copy from [p:p + n) to [q:q + n)

```
This is a nasty variant of a K&R C-style interface. It is easy to reverse the "to" and "from" arguments.

Use `const` for the "from" argument:

```cpp
void copy_n(const T* p, T* q, int n);  // copy from [p:p + n) to [q:q + n)

```
##### Exception

If the order of the parameters is not important, there is no problem:

```cpp
int max(int a, int b);

```
##### Alternative

Don't pass arrays as pointers, pass an object representing a range (e.g., a `span`):

```cpp
void copy_n(span<const T> p, span<T> q);  // copy from p to q

```
##### Alternative

Define a `struct` as the parameter type and name the fields for those parameters accordingly:

```cpp
struct SystemParams {
    string config_file;
    string output_path;
    seconds timeout;
};
void initialize(SystemParams p);

```
This tends to make invocations of this clear to future readers, as the parameters
are often filled in by name at the call site.

##### Enforcement

(Simple) Warn if two consecutive parameters share the same type.

