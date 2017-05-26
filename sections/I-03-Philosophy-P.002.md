### <a name="Rp-Cplusplus"></a>P.2: Write in ISO Standard C++

##### Reason

This is a set of guidelines for writing ISO Standard C++.

##### Note

There are environments where extensions are necessary, e.g., to access system resources.
In such cases, localize the use of necessary extensions and control their use with non-core Coding Guidelines.  If possible, build interfaces that encapsulate the extensions so they can be turned off or compiled away on systems that do not support those extensions.

Extensions often do not have rigorously defined semantics.  Even extensions that
are common and implemented by multiple compilers may have slightly different
behaviors and edge case behavior as a direct result of *not* having a rigorous
standard definition.  With sufficient use of any such extension, expected
portability will be impacted.

##### Note

Using valid ISO C++ does not guarantee portability (let alone correctness).
Avoid dependence on undefined behavior (e.g., [undefined order of evaluation](I-10-Expressions%20and%20Statements-ES.043.md#Res-order))
and be aware of constructs with implementation defined meaning (e.g., `sizeof(int)`).

##### Note

There are environments where restrictions on use of standard C++ language or library features are necessary, e.g., to avoid dynamic memory allocation as required by aircraft control software standards.
In such cases, control their (dis)use with an extension of these Coding Guidelines customized to the specific environment.

##### Enforcement

Use an up-to-date C++ compiler (currently C++11 or C++14) with a set of options that do not accept extensions.

