### <a name="Rl-camel"></a>NL.10: Avoid CamelCase

##### Reason

The use of underscores to separate parts of a name is the original C and C++ style and used in the C++ standard library.
If you prefer CamelCase, you have to choose among different flavors of camelCase.

##### Note

This rule is a default to use only if you have a choice.
Often, you don't have a choice and must follow an established style for [consistency](I-24-Naming and layout rules-NL.008.md#Rl-name).
The need for consistency beats personal taste.

##### Example

[Stroustrup](http://www.stroustrup.com/Programming/PPP-style.pdf):
ISO Standard, but with upper case used for your own types and concepts:

* `int`
* `vector`
* `My_map`

##### Enforcement

Impossible.

