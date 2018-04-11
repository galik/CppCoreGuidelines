# <a name="main"></a>C++ Core Guidelines Tutorial

June 20, 2017

Editors:

* [Galik.Bool](https://github.com/galik)

##Sections

* [In: Introduction](#S-introduction)
* [V: Variables](#S-vars)

# <a name="S-introduction"></a>In: Introduction

### <a name="In-helloworld"></a>In.1: Smallest program

The smallest program that can be written in `C++` is the following:

```cpp
int main() {}
```

It contains one *function* called the *main* function which every `C++` program must have. In `C++` every function, inclusing *main()* has four parts:

* Return typed - `int`
* Name         - `main`
* Parameters   - `()`
* Body         - `{}`

The main function always has the return type `int` meaning an *integer* but other functions can return any type ([see types](#T-types)). Returning an `int` means it it must return a whole number. The standard libraries predefine two symbols that represent common return values from the *main()* function:

```cpp
EXIT_FAIL
EXIT_SUCCESS
```

Unlike other functions the *main()* function does not need to explicitly *return* anything. If it doesn't the compiler generates an *implicit return* of `EXIT_SUCCESS`.

The above program is therefore equivalent to this:

```cpp
int main()
{
	return EXIT_SUCCESS;	
}
```

# <a name="S-variables"></a>Var: Variables

`C++` programs store their data in *variables*. A variable has three attributes:

eg.

```cpp
int i = 5;
```

* A type        - `int`
* An identifier - `i`
* A value       - `5`





















