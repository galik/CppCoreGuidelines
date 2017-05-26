### <a name="Res-MACROS"></a>ES.33: If you must use macros, give them unique names

##### Reason

Macros do not obey scope rules.

##### Example

```cpp
#define MYCHAR        /* BAD, will eventually clash with someone else's MYCHAR*/

#define ZCORP_CHAR    /* Still evil, but less likely to clash */

```
##### Note

Avoid macros if you can: [ES.30](I-10-Expressions and Statements-ES.030.md#Res-macros), [ES.31](I-10-Expressions and Statements-ES.031.md#Res-macros2), and [ES.32](I-10-Expressions and Statements-ES.032.md#Res-ALL_CAPS).
However, there are billions of lines of code littered with macros and a long tradition for using and overusing macros.
If you are forced to use macros, use long names and supposedly unique prefixes (e.g., your organization's name) to lower the likelihood of a clash.

##### Enforcement

Warn against short macro names.

