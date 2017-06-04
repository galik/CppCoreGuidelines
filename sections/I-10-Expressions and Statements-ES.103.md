### <a name="Res-overflow"></a>ES.103: Don't overflow

##### Reason

Overflow usually makes your numeric algorithm meaningless.
Incrementing a value beyond a maximum value can lead to memory corruption and undefined behavior.

##### Example, bad

```cpp
int a[10];
a[10] = 7;   // bad

int n = 0;
while (n++ < 10)
    a[n - 1] = 9; // bad (twice)

```
##### Example, bad

```cpp
int n = numeric_limits<int>::max();
int m = n + 1;   // bad

```
##### Example, bad

```cpp
int area(int h, int w) { return h * w; }

auto a = area(10'000'000, 100'000'000);   // bad

```
##### Exception

Use unsigned types if you really want modulo arithmetic.

**Alternative**: For critical applications that can afford some overhead, use a range-checked integer and/or floating-point type.

##### Enforcement

???

