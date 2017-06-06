# <a name="S-expr"></a>ES: Expressions and Statements

Expressions and statements are the lowest and most direct way of expressing actions and computation. Declarations in local scopes are statements.

For naming, commenting, and indentation rules, see [NL: Naming and layout](I-24-Naming%20and%20layout%20rules.md#S-naming).

General rules:

* [ES.1: Prefer the standard library to other libraries and to "handcrafted code"](I-10-Expressions%20and%20Statements-ES.001.md#Res-lib)
* [ES.2: Prefer suitable abstractions to direct use of language features](I-10-Expressions%20and%20Statements-ES.002.md#Res-abstr)

Declaration rules:

* [ES.5: Keep scopes small](I-10-Expressions%20and%20Statements-ES.005.md#Res-scope)
* [ES.6: Declare names in for-statement initializers and conditions to limit scope](I-10-Expressions%20and%20Statements-ES.006.md#Res-cond)
* [ES.7: Keep common and local names short, and keep uncommon and nonlocal names longer](I-10-Expressions%20and%20Statements-ES.007.md#Res-name-length)
* [ES.8: Avoid similar-looking names](I-10-Expressions%20and%20Statements-ES.008.md#Res-name-similar)
* [ES.9: Avoid `ALL_CAPS` names](I-10-Expressions%20and%20Statements-ES.009.md#Res-not-CAPS)
* [ES.10: Declare one name (only) per declaration](I-10-Expressions%20and%20Statements-ES.010.md#Res-name-one)
* [ES.11: Use `auto` to avoid redundant repetition of type names](I-10-Expressions%20and%20Statements-ES.011.md#Res-auto)
* [ES.12: Do not reuse names in nested scopes](I-10-Expressions%20and%20Statements-ES.012.md#Res-reuse)
* [ES.20: Always initialize an object](I-10-Expressions%20and%20Statements-ES.020.md#Res-always)
* [ES.21: Don't introduce a variable (or constant) before you need to use it](I-10-Expressions%20and%20Statements-ES.021.md#Res-introduce)
* [ES.22: Don't declare a variable until you have a value to initialize it with](I-10-Expressions%20and%20Statements-ES.022.md#Res-init)
* [ES.23: Prefer the `{}`-initializer syntax](I-10-Expressions%20and%20Statements-ES.023.md#Res-list)
* [ES.24: Use a `unique_ptr<T>` to hold pointers](I-10-Expressions%20and%20Statements-ES.024.md#Res-unique)
* [ES.25: Declare an object `const` or `constexpr` unless you want to modify its value later on](I-10-Expressions%20and%20Statements-ES.025.md#Res-const)
* [ES.26: Don't use a variable for two unrelated purposes](I-10-Expressions%20and%20Statements-ES.026.md#Res-recycle)
* [ES.27: Use `std::array` or `stack_array` for arrays on the stack](I-10-Expressions%20and%20Statements-ES.027.md#Res-stack)
* [ES.28: Use lambdas for complex initialization, especially of `const` variables](I-10-Expressions%20and%20Statements-ES.028.md#Res-lambda-init)
* [ES.30: Don't use macros for program text manipulation](I-10-Expressions%20and%20Statements-ES.030.md#Res-macros)
* [ES.31: Don't use macros for constants or "functions"](I-10-Expressions%20and%20Statements-ES.031.md#Res-macros2)
* [ES.32: Use `ALL_CAPS` for all macro names](I-10-Expressions%20and%20Statements-ES.032.md#Res-ALL_CAPS)
* [ES.33: If you must use macros, give them unique names](I-10-Expressions%20and%20Statements-ES.033.md#Res-MACROS)
* [ES.34: Don't define a (C-style) variadic function](I-10-Expressions%20and%20Statements-%20ES.034.md#Res-ellipses)

Expression rules:

* [ES.40: Avoid complicated expressions](I-10-Expressions%20and%20Statements-ES.040.md#Res-complicated)
* [ES.41: If in doubt about operator precedence, parenthesize](I-10-Expressions%20and%20Statements-ES.041.md#Res-parens)
* [ES.42: Keep use of pointers simple and straightforward](I-10-Expressions%20and%20Statements-ES.042.md#Res-ptr)
* [ES.43: Avoid expressions with undefined order of evaluation](I-10-Expressions%20and%20Statements-ES.043.md#Res-order)
* [ES.44: Don't depend on order of evaluation of function arguments](I-10-Expressions%20and%20Statements-ES.044.md#Res-order-fct)
* [ES.45: Avoid "magic constants"; use symbolic constants](I-10-Expressions%20and%20Statements-ES.045.md#Res-magic)
* [ES.46: Avoid narrowing conversions](I-10-Expressions%20and%20Statements-ES.046.md#Res-narrowing)
* [ES.47: Use `nullptr` rather than `0` or `NULL`](I-10-Expressions%20and%20Statements-ES.047.md#Res-nullptr)
* [ES.48: Avoid casts](I-10-Expressions%20and%20Statements-ES.048.md#Res-casts)
* [ES.49: If you must use a cast, use a named cast](I-10-Expressions%20and%20Statements-ES.049.md#Res-casts-named)
* [ES.50: Don't cast away `const`](I-10-Expressions%20and%20Statements-ES.050.md#Res-casts-const)
* [ES.55: Avoid the need for range checking](I-10-Expressions%20and%20Statements-ES.055.md#Res-range-checking)
* [ES.56: Write `std::move()` only when you need to explicitly move an object to another scope](I-10-Expressions%20and%20Statements-ES.056.md#Res-move)
* [ES.60: Avoid `new` and `delete` outside resource management functions](I-10-Expressions%20and%20Statements-ES.060.md#Res-new)
* [ES.61: Delete arrays using `delete[]` and non-arrays using `delete`](I-10-Expressions%20and%20Statements-ES.061.md#Res-del)
* [ES.62: Don't compare pointers into different arrays](I-10-Expressions%20and%20Statements-ES.062.md#Res-arr2)
* [ES.63: Don't slice](I-10-Expressions%20and%20Statements-ES.063.md#Res-slice)
* [ES.64: Use the `T{e}`notation for construction](I-10-Expressions%20and%20Statements-ES.064.md#Res-construct)
* [ES.65: Don't dereference an invalid pointer](I-10-Expressions%20and%20Statements-ES.065.md#Res-deref)

Statement rules:

* [ES.70: Prefer a `switch`-statement to an `if`-statement when there is a choice](I-10-Expressions%20and%20Statements-ES.070.md#Res-switch-if)
* [ES.71: Prefer a range-`for`-statement to a `for`-statement when there is a choice](I-10-Expressions%20and%20Statements-ES.071.md#Res-for-range)
* [ES.72: Prefer a `for`-statement to a `while`-statement when there is an obvious loop variable](I-10-Expressions%20and%20Statements-ES.072.md#Res-for-while)
* [ES.73: Prefer a `while`-statement to a `for`-statement when there is no obvious loop variable](I-10-Expressions%20and%20Statements-ES.073.md#Res-while-for)
* [ES.74: Prefer to declare a loop variable in the initializer part of a `for`-statement](I-10-Expressions%20and%20Statements-ES.074.md#Res-for-init)
* [ES.75: Avoid `do`-statements](I-10-Expressions%20and%20Statements-ES.075.md#Res-do)
* [ES.76: Avoid `goto`](I-10-Expressions%20and%20Statements-ES.076.md#Res-goto)
* [ES.77: Minimize the use of `break` and `continue` in loops](I-10-Expressions%20and%20Statements-ES.077.md#Res-continue)
* [ES.78: Always end a non-empty `case` with a `break`](I-10-Expressions%20and%20Statements-ES.078.md#Res-break)
* [ES.79: Use `default` to handle common cases (only)](I-10-Expressions%20and%20Statements-ES.079.md#Res-default)
* [ES.84: Don't (try to) declare a local variable with no name](I-10-Expressions%20and%20Statements-ES.084.md#Res-noname)
* [ES.85: Make empty statements visible](I-10-Expressions%20and%20Statements-ES.085.md#Res-empty)
* [ES.86: Avoid modifying loop control variables inside the body of raw for-loops](I-10-Expressions%20and%20Statements-ES.086.md#Res-loop-counter)

Arithmetic rules:

* [ES.100: Don't mix signed and unsigned arithmetic](I-10-Expressions%20and%20Statements-ES.100.md#Res-mix)
* [ES.101: Use unsigned types for bit manipulation](I-10-Expressions%20and%20Statements-ES.101.md#Res-unsigned)
* [ES.102: Use signed types for arithmetic](I-10-Expressions%20and%20Statements-ES.102.md#Res-signed)
* [ES.103: Don't overflow](I-10-Expressions%20and%20Statements-ES.103.md#Res-overflow)
* [ES.104: Don't underflow](I-10-Expressions%20and%20Statements-ES.104.md#Res-underflow)
* [ES.105: Don't divide by zero](I-10-Expressions%20and%20Statements-ES.105.md#Res-zero)
* [ES.106: Don't try to avoid negative values by using `unsigned`](I-10-Expressions%20and%20Statements-ES.106.md#Res-nonnegative)
* [ES.107: Don't use `unsigned` for subscripts](I-10-Expressions%20and%20Statements-ES.107.md#Res-subscripts)

