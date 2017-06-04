# <a name="S-not"></a>NR: Non-Rules and myths

This section contains rules and guidelines that are popular somewhere, but that we deliberately don't recommend.
We know full well that there have been times and places where these rules made sense, and we have used them ourselves at times.
However, in the context of the styles of programming we recommend and support with the guidelines, these "non-rules" would do harm.

Even today, there can be contexts where the rules make sense.
For example, lack of suitable tool support can make exceptions unsuitable in hard-real-time systems,
but please don't blindly trust "common wisdom" (e.g., unsupported statements about "efficiency");
such "wisdom" may be based on decades-old information or experienced from languages with very different properties than C++
(e.g., C or Java).

The positive arguments for alternatives to these non-rules are listed in the rules offered as "Alternatives".

Non-rule summary:

* [NR.1: Don't: All declarations should be at the top of a function](I-20-Non-Rules%20and%20myths-NR.001.md#Rnr-top)
* [NR.2: Don't: Have only a single `return`-statement in a function](I-20-Non-Rules%20and%20myths-NR.002.md#Rnr-single-return)
* [NR.3: Don't: Don't use exceptions](I-20-Non-Rules%20and%20myths-NR.003.md#Rnr-no-exceptions)
* [NR.4: Don't: Place each class declaration in its own source file](I-20-Non-Rules%20and%20myths-NR.004.md#Rnr-lots-of-files)
* [NR.5: Don't: Don't do substantive work in a constructor; instead use two-phase initialization](I-20-Non-Rules%20and%20myths-NR.005.md#Rnr-two-phase-init)
* [NR.6: Don't: Place all cleanup actions at the end of a function and `goto exit`](I-20-Non-Rules%20and%20myths-NR.006.md#Rnr-goto-exit)
* [NR.7: Don't: Make all data members `protected`](I-20-Non-Rules%20and%20myths-NR.007.md#Rnr-protected-data)
* ???

