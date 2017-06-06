### <a name="Renum-class"></a>Enum.3: Prefer class enums over "plain" enums

##### Reason

To minimize surprises: traditional enums convert to int too readily.

##### Example

```cpp
void Print_color(int color);

enum Web_color { red = 0xFF0000, green = 0x00FF00, blue = 0x0000FF };
enum Product_info { Red = 0, Purple = 1, Blue = 2 };

Web_color webby = Web_color::blue;

// Clearly at least one of these calls is buggy.
Print_color(webby);
Print_color(Product_info::Blue);

```
Instead use an `enum class`:

```cpp
void Print_color(int color);

enum class Web_color { red = 0xFF0000, green = 0x00FF00, blue = 0x0000FF };
enum class Product_info { red = 0, purple = 1, blue = 2 };

Web_color webby = Web_color::blue;
Print_color(webby);  // Error: cannot convert Web_color to int.
Print_color(Product_info::Red);  // Error: cannot convert Product_info to int.

```
##### Enforcement

(Simple) Warn on any non-class `enum` definition.

