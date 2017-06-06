### <a name="Ri-array"></a>I.13: Do not pass an array as a single pointer

##### Reason

 (pointer, size)-style interfaces are error-prone. Also, a plain pointer (to array) must rely on some convention to allow the callee to determine the size.

##### Example

Consider:

```cpp
void copy_n(const T* p, T* q, int n); // copy from [p:p + n) to [q:q + n)

```
What if there are fewer than `n` elements in the array pointed to by `q`? Then, we overwrite some probably unrelated memory.
What if there are fewer than `n` elements in the array pointed to by `p`? Then, we read some probably unrelated memory.
Either is undefined behavior and a potentially very nasty bug.

##### Alternative

Consider using explicit spans:

```cpp
void copy(span<const T> r, span<T> r2); // copy r to r2

```
##### Example, bad

Consider:

```cpp
void draw(Shape* p, int n);  // poor interface; poor code
Circle arr[10];
// ...
draw(arr, 10);

```
Passing `10` as the `n` argument may be a mistake: the most common convention is to assume \[`0`:`n`) but that is nowhere stated. Worse is that the call of `draw()` compiled at all: there was an implicit conversion from array to pointer (array decay) and then another implicit conversion from `Circle` to `Shape`. There is no way that `draw()` can safely iterate through that array: it has no way of knowing the size of the elements.

**Alternative**: Use a support class that ensures that the number of elements is correct and prevents dangerous implicit conversions. For example:

```cpp
void draw2(span<Circle>);
Circle arr[10];
// ...
draw2(span<Circle>(arr));  // deduce the number of elements
draw2(arr);    // deduce the element type and array size

void draw3(span<Shape>);
draw3(arr);    // error: cannot convert Circle[10] to span<Shape>

```
This `draw2()` passes the same amount of information to `draw()`, but makes the fact that it is supposed to be a range of `Circle`s explicit. See ???.

##### Exception

Use `zstring` and `czstring` to represent a C-style, zero-terminated strings.
But when doing so, use `string_span` from the [GSL](#GSL) to prevent range errors.

##### Enforcement

* (Simple) ((Bounds)) Warn for any expression that would rely on implicit conversion of an array type to a pointer type. Allow exception for zstring/czstring pointer types.
* (Simple) ((Bounds)) Warn for any arithmetic operation on an expression of pointer type that results in a value of pointer type. Allow exception for zstring/czstring pointer types.

