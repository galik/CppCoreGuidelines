### <a name="Rio-endl"></a>SL.io.50: Avoid `endl`

### Reason

The `endl` manipulator is mostly equivalent to `'\n'` and `"\n"`;
as most commonly used it simply slows down output by doing redundant `flush()`s.
This slowdown can be significant compared to `printf`-style output.

##### Example

```cpp
cout << "Hello, World!" << endl;    // two output operations and a flush
cout << "Hello, World!\n";          // one output operation and no flush

```
##### Note

For `cin`/`cout` (and equivalent) interaction, there is no reason to flush; that's done automatically.
For writing to a file, there is rarely a need to `flush`.

##### Note

Apart from the (occasionally important) issue of performance,
the choice between `'\n'` and `endl` is almost completely aesthetic.

## <a name="SS-regex"></a>SL.regex: Regex

`<regex>` is the standard C++ regular expression library.
It supports a variety of regular expression pattern conventions.

## <a name="SS-chrono"></a>SL.chrono: Time

`<chrono>` (defined in namespace `std::chrono`) provides the notions of `time_point` and `duration` together with functions for
outputting time in various units.
It provides clocks for registering `time_points`.

## <a name="SS-clib"></a>SL.C: The C standard library

???

C standard library rule summary:

* [S.C.1: Don't use setjmp/longjmp](I-18-The Standard Library-SL.C.001.md#Rclib-jmp)
* [???](#???)
* [???](#???)

