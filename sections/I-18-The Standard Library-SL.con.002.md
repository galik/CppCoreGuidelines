### <a name="Rsl-vector"></a>SL.con.2: Prefer using STL `vector` by default unless you have a reason to use a different container

##### Reason

`vector` and `array` are the only standard containers that offer the fastest general-purpose access (random access, including being vectorization-friendly), the fastest default access pattern (begin-to-end or end-to-begin is prefetcher-friendly), and the lowest space overhead (contiguous layout has zero per-element overhead, which is cache-friendly).
Usually you need to add and remove elements from the container, so use `vector` by default; if you don't need to modify the container's size, use `array`.

Even when other containers seem more suited, such a `map` for O(log N) lookup performance or a `list` for efficient insertion in the middle, a `vector` will usually still perform better for containers up to a few KB in size.

##### Note

`string` should not be used as a container of individual characters. A `string` is a textual string; if you want a container of characters, use `vector</*char_type*/>` or `array</*char_type*/>` instead.

##### Exceptions

If you have a good reason to use another container, use that instead. For example:

* If `vector` suits your needs but you don't need the container to be variable size, use `array` instead.

* If you want a dictionary-style lookup container that guarantees O(K) or O(log N) lookups, the container will be larger (more than a few KB) and you perform frequent inserts so that the overhead of maintaining a sorted `vector` is infeasible, go ahead and use an `unordered_map` or `map` instead.

##### Enforcement

* Flag a `vector` whose size never changes after construction (such as because it's `const` or because no non-`const` functions are called on it). To fix: Use an `array` instead.

