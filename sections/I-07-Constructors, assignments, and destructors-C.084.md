### <a name="Rc-swap-fail"></a>C.84: A `swap` function may not fail

##### Reason

 `swap` is widely used in ways that are assumed never to fail and programs cannot easily be written to work correctly in the presence of a failing `swap`. The standard-library containers and algorithms will not work correctly if a swap of an element type fails.

##### Example, bad

```cpp
void swap(My_vector& x, My_vector& y)
{
    auto tmp = x;   // copy elements
    x = y;
    y = tmp;
}

```
This is not just slow, but if a memory allocation occurs for the elements in `tmp`, this `swap` may throw and would make STL algorithms fail if used with them.

##### Enforcement

(Simple) When a class has a `swap` member function, it should be declared `noexcept`.

