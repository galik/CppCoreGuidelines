# <a name="S-naming"></a>NL: Naming and layout rules

Consistent naming and layout are helpful.
If for no other reason because it minimizes "my style is better than your style" arguments.
However, there are many, many, different styles around and people are passionate about them (pro and con).
Also, most real-world projects includes code from many sources, so standardizing on a single style for all code is often impossible.
We present a set of rules that you might use if you have no better ideas, but the real aim is consistency, rather than any particular rule set.
IDEs and tools can help (as well as hinder).

Naming and layout rules:

* [NL.1: Don't say in comments what can be clearly stated in code](I-24-Naming and layout rules-NL.001.md#Rl-comments)
* [NL.2: State intent in comments](I-24-Naming and layout rules-NL.002.md#Rl-comments-intent)
* [NL.3: Keep comments crisp](I-24-Naming and layout rules-NL.003.md#Rl-comments-crisp)
* [NL.4: Maintain a consistent indentation style](I-24-Naming and layout rules-NL.004.md#Rl-indent)
* [NL.5: Don't encode type information in names](I-24-Naming and layout rules-NL.005.md#Rl-name-type)
* [NL.7: Make the length of a name roughly proportional to the length of its scope](I-24-Naming and layout rules-NL.007.md#Rl-name-length)
* [NL.8: Use a consistent naming style](I-24-Naming and layout rules-NL.008.md#Rl-name)
* [NL.9: Use `ALL_CAPS` for macro names only](I-24-Naming and layout rules-NL.009.md#Rl-all-caps)
* [NL.10: Avoid CamelCase](I-24-Naming and layout rules-NL.010.md#Rl-camel)
* [NL.11: Make literals readable](I-24-Naming and layout rules-NL.011.md#Rl-literals)
* [NL.15: Use spaces sparingly](I-24-Naming and layout rules-NL.015.md#Rl-space)
* [NL.16: Use a conventional class member declaration order](I-24-Naming and layout rules-NL.016.md#Rl-order)
* [NL.17: Use K&R-derived layout](I-24-Naming and layout rules-NL.017.md#Rl-knr)
* [NL.18: Use C++-style declarator layout](I-24-Naming and layout rules-NL.018.md#Rl-ptr)
* [NL.19: Avoid names that are easily misread](I-24-Naming and layout rules-NL.019.md#Rl-misread)
* [NL.20: Don't place two statements on the same line](I-24-Naming and layout rules-NL.020.md#Rl-stmt)
* [NL.21: Declare one name (only) per declaration](I-24-Naming and layout rules-NL.021.md#Rl-dcl)
* [NL.25: Don't use `void` as an argument type](I-24-Naming and layout rules-NL.025.md#Rl-void)
* [NL.26: Use conventional `const` notation](I-24-Naming and layout rules-NL.026.md#Rl-const)

Most of these rules are aesthetic and programmers hold strong opinions.
IDEs also tend to have defaults and a range of alternatives.
These rules are suggested defaults to follow unless you have reasons not to.

We have had comments to the effect that naming and layout are so personal and/or arbitrary that we should not try to "legislate" them.
We are not "legislating" (see the previous paragraph).
However, we have had many requests for a set of naming and layout conventions to use when there are no external constraints.

More specific and detailed rules are easier to enforce.

These rules bear a strong resemblance to the recommendations in the [PPP Style Guide](http://www.stroustrup.com/Programming/PPP-style.pdf)
written in support of Stroustrup's [Programming: Principles and Practice using C++](http://www.stroustrup.com/programming.html).

