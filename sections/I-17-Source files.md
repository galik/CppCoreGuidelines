# <a name="S-source"></a>SF: Source files

Distinguish between declarations (used as interfaces) and definitions (used as implementations).
Use header files to represent interfaces and to emphasize logical structure.

Source file rule summary:

* [SF.1: Use a `.cpp` suffix for code files and `.h` for interface files if your project doesn't already follow another convention](I-17-Source%20files-SF.001.md#Rs-file-suffix)
* [SF.2: A `.h` file may not contain object definitions or non-inline function definitions](I-17-Source%20files-SF.002.md#Rs-inline)
* [SF.3: Use `.h` files for all declarations used in multiple source files](I-17-Source%20files-SF.003.md#Rs-declaration-header)
* [SF.4: Include `.h` files before other declarations in a file](I-17-Source%20files-SF.004.md#Rs-include-order)
* [SF.5: A `.cpp` file must include the `.h` file(s) that defines its interface](I-17-Source%20files-SF.005.md#Rs-consistency)
* [SF.6: Use `using namespace` directives for transition, for foundation libraries (such as `std`), or within a local scope (only)](I-17-Source%20files-SF.006.md#Rs-using)
* [SF.7: Don't write `using namespace` in a header file](I-17-Source%20files-SF.007.md#Rs-using-directive)
* [SF.8: Use `#include` guards for all `.h` files](I-17-Source%20files-SF.008.md#Rs-guards)
* [SF.9: Avoid cyclic dependencies among source files](I-17-Source%20files-SF.009.md#Rs-cycles)
* [SF.10: Avoid dependencies on implicitly `#included` names](I-17-Source%20files-SF.010.md#Rs-implicit)

* [SF.20: Use `namespace`s to express logical structure](I-17-Source%20files-SF.020.md#Rs-namespace)
* [SF.21: Don't use an unnamed (anonymous) namespace in a header](I-17-Source%20files-SF.021.md#Rs-unnamed)
* [SF.22: Use an unnamed (anonymous) namespace for all internal/nonexported entities](I-17-Source%20files-SF.022.md#Rs-unnamed2)

