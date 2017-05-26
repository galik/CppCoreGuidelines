# <a name="main"></a>C++ Core Guidelines

May 23, 2017


Editors:

* [Bjarne Stroustrup](http://www.stroustrup.com)
* [Herb Sutter](http://herbsutter.com/)

This document is a very early draft. It is inkorrekt, incompleat, and pÂµÃoorly formatted.
Had it been an open source (code) project, this would have been release 0.7.
Copying, use, modification, and creation of derivative works from this project is licensed under an MIT-style license.
Contributing to this project requires agreeing to a Contributor License. See the accompanying [LICENSE](LICENSE) file for details.
We make this project available to "friendly users" to use, copy, modify, and derive from, hoping for constructive input.

Comments and suggestions for improvements are most welcome.
We plan to modify and extend this document as our understanding improves and the language and the set of available libraries improve.
When commenting, please note [the introduction](I-02-Introduction.md#S-introduction) that outlines our aims and general approach.
The list of contributors is [here](I-21-References.md#SS-ack).

Problems:

* The sets of rules have not been thoroughly checked for completeness, consistency, or enforceability.
* Triple question marks (???) mark known missing information
* Update reference sections; many pre-C++11 sources are too old.
* For a more-or-less up-to-date to-do list see: [To-do: Unclassified proto-rules](I-30-Unclassified proto-rules.md#S-unclassified)

You can [read an explanation of the scope and structure of this Guide](I-01-Abstract.md#S-abstract) or just jump straight in:

* [In: Introduction](I-02-Introduction.md#S-introduction)
* [P: Philosophy](I-03-Philosophy.md#S-philosophy)
* [I: Interfaces](I-04-Interfaces.md#S-interfaces)
* [F: Functions](I-05-Functions.md#S-functions)
* [C: Classes and class hierarchies](I-06-Classes and Class Hierarchies.md#S-class)
* [Enum: Enumerations](I-08-Enumerations.md#S-enum)
* [R: Resource management](I-09-Resource management.md#S-resource)
* [ES: Expressions and statements](I-10-Expressions and Statements.md#S-expr)
* [Per: Performance](I-11-Performance.md#S-performance)
* [CP: Concurrency](I-12-Concurrency and Parallelism.md#S-concurrency)
* [E: Error handling](I-13-Error handling.md#S-errors)
* [Con: Constants and immutability](I-14-Constants and Immutability.md#S-const)
* [T: Templates and generic programming](I-15-Templates and generic programming.md#S-templates)
* [CPL: C-style programming](I-16-C-style programming.md#S-cpl)
* [SF: Source files](I-17-Source files.md#S-source)
* [SL: The Standard library](I-18-The Standard Library.md#S-stdlib)

Supporting sections:

* [A: Architectural Ideas](I-19-Architectural Ideas.md#S-A)
* [N: Non-Rules and myths](I-20-Non-Rules and myths.md#S-not)
* [RF: References](I-21-References.md#S-references)
* [Pro: Profiles](I-22-Profiles.md#S-profile)
* [GSL: Guideline support library](I-23-Guideline support library.md#S-gsl)
* [NL: Naming and layout](I-24-Naming and layout rules.md#S-naming)
* [FAQ: Answers to frequently asked questions](I-25-Answers to frequently asked questions.md#S-faq)
* [Appendix A: Libraries](I-26-Libraries.md#S-libraries)
* [Appendix B: Modernizing code](I-27-Modernizing code.md#S-modernizing)
* [Appendix C: Discussion](I-28-Discussion.md#S-discussion)
* [Glossary](I-29-Glossary.md#S-glossary)
* [To-do: Unclassified proto-rules](I-30-Unclassified proto-rules.md#S-unclassified)

You can sample rules for specific language features:

* assignment:
[regular types](I-06-Classes and Class Hierarchies-C.011.md#Rc-regular) --
[prefer initialization](I-07-Constructors, assignments, and destructors-C.049.md#Rc-initialize) --
[copy](#Rc-copy-semantics) --
[move](#Rc-move-semantics) --
[other operations](I-07-Constructors, assignments, and destructors-C.022.md#Rc-matched) --
[default](I-07-Constructors, assignments, and destructors-C.080.md#Rc-eqdefault)
* `class`:
[data](I-06-Classes and Class Hierarchies-C.001.md#Rc-org) --
[invariant](I-06-Classes and Class Hierarchies-C.002.md#Rc-struct) --
[members](I-06-Classes and Class Hierarchies-C.004.md#Rc-member) --
[helpers](I-06-Classes and Class Hierarchies-C.005.md#Rc-helper) --
[concrete types](I-06-Classes and Class Hierarchies-C.009.md#SS-concrete) --
[ctors, =, and dtors](I-07-Constructors, assignments, and destructors.md#S-ctor) --
[hierarchy](I-07-Constructors, assignments, and destructors-C.089.md#SS-hier) --
[operators](I-07-Constructors, assignments, and destructors-C.153.md#SS-overload)
* `concept`:
[rules](I-15-Templates and generic programming-T.005.md#SS-concepts) --
[in generic programming](I-15-Templates and generic programming-T.001.md#Rt-raise) --
[template arguments](#RT-concepts) --
[semantics](I-15-Templates and generic programming-T.020.md#Rt-low)
* constructor:
[invariant](I-06-Classes and Class Hierarchies-C.002.md#Rc-struct) --
[establish invariant](I-07-Constructors, assignments, and destructors-C.040.md#Rc-ctor) --
[`throw`](I-07-Constructors, assignments, and destructors-C.042.md#Rc-throw) --
[default](I-07-Constructors, assignments, and destructors-C.043.md#Rc-default0) --
[not needed](I-07-Constructors, assignments, and destructors-C.045.md#Rc-default) --
[`explicit`](I-07-Constructors, assignments, and destructors-C.046.md#Rc-explicit) --
[delegating](I-07-Constructors, assignments, and destructors-C.051.md#Rc-delegating) --
[`virtual`](#RC-ctor-virtual)
* derived `class`:
[when to use](I-07-Constructors, assignments, and destructors-C.120.md#Rh-domain) --
[as interface](I-07-Constructors, assignments, and destructors-C.121.md#Rh-abstract) --
[destructors](I-07-Constructors, assignments, and destructors-C.127.md#Rh-dtor) --
[copy](I-07-Constructors, assignments, and destructors-C.130.md#Rh-copy) --
[getters and setters](I-07-Constructors, assignments, and destructors-C.131.md#Rh-get) --
[multiple inheritance](I-07-Constructors, assignments, and destructors-C.135.md#Rh-mi-interface) --
[overloading](I-07-Constructors, assignments, and destructors-C.138.md#Rh-using) --
[slicing](I-07-Constructors, assignments, and destructors-C.067.md#Rc-copy-virtual) --
[`dynamic_cast`](I-07-Constructors, assignments, and destructors-C.146.md#Rh-dynamic_cast)
* destructor:
[and constructors](I-07-Constructors, assignments, and destructors-C.022.md#Rc-matched) --
[when needed?](I-07-Constructors, assignments, and destructors-C.030.md#Rc-dtor) --
[may not fail](I-07-Constructors, assignments, and destructors-C.036.md#Rc-dtor-fail)
* exception:
[errors](I-13-Error handling.md#S-errors) --
[`throw`](I-13-Error handling-E.002.md#Re-throw) --
[for errors only](I-13-Error handling-E.003.md#Re-errors) --
[`noexcept`](I-13-Error handling-E.012.md#Re-noexcept) --
[minimize `try`](I-13-Error handling-E.018.md#Re-catch) --
[what if no exceptions?](I-13-Error handling-E.027.md#Re-no-throw-codes)
* `for`:
[range-for and for](I-10-Expressions and Statements-ES.071.md#Res-for-range) --
[for and while](I-10-Expressions and Statements-ES.072.md#Res-for-while) --
[for-initializer](I-10-Expressions and Statements-ES.074.md#Res-for-init) --
[empty body](I-10-Expressions and Statements-ES.085.md#Res-empty) --
[loop variable](I-10-Expressions and Statements-ES.086.md#Res-loop-counter) --
[loop variable type ???](#Res-???)
* function:
[naming](I-05-Functions-F.001.md#Rf-package) --
[single operation](I-05-Functions-F.002.md#Rf-logical) --
[no throw](I-05-Functions-F.006.md#Rf-noexcept) --
[arguments](I-05-Functions-F.007.md#Rf-smart) --
[argument passing](I-05-Functions-F.015.md#Rf-conventional) --
[multiple return values](I-05-Functions-F.021.md#Rf-out-multi) --
[pointers](I-05-Functions-F.042.md#Rf-return-ptr) --
[lambdas](I-05-Functions-F.050.md#Rf-capture-vs-overload)
* `inline`:
[small functions](I-05-Functions-F.005.md#Rf-inline) --
[in headers](I-17-Source files-SF.002.md#Rs-inline)
* initialization:
[always](I-10-Expressions and Statements-ES.020.md#Res-always) --
[prefer `{}`](I-10-Expressions and Statements-ES.023.md#Res-list) --
[lambdas](I-10-Expressions and Statements-ES.028.md#Res-lambda-init) --
[in-class initializers](I-07-Constructors, assignments, and destructors-C.048.md#Rc-in-class-initializer) --
[class members](I-07-Constructors, assignments, and destructors-C.049.md#Rc-initialize) --
[factory functions](I-07-Constructors, assignments, and destructors-C.050.md#Rc-factory)
* lambda expression:
[when to use](I-07-Constructors, assignments, and destructors-C.089.md#SS-lambdas)
* operator:
[conventional](I-07-Constructors, assignments, and destructors-C.160.md#Ro-conventional) --
[avoid conversion operators](I-07-Constructors, assignments, and destructors-C.160.md#Ro-conventional) --
[and lambdas](I-07-Constructors, assignments, and destructors-C.170.md#Ro-lambda)
* `public`, `private`, and `protected`:
[information hiding](I-06-Classes and Class Hierarchies-C.009.md#Rc-private) --
[consistency](I-07-Constructors, assignments, and destructors-C.134.md#Rh-public) --
[`protected`](I-07-Constructors, assignments, and destructors-C.133.md#Rh-protected)
* `static_assert`:
[compile-time checking](I-03-Philosophy-P.005.md#Rp-compile-time) --
[and concepts](I-15-Templates and generic programming-T.150.md#Rt-check-class)
* `struct`:
[for organizing data](I-06-Classes and Class Hierarchies-C.001.md#Rc-org) --
[use if no invariant](I-06-Classes and Class Hierarchies-C.002.md#Rc-struct) --
[no private members](I-06-Classes and Class Hierarchies-C.008.md#Rc-class)
* `template`:
[abstraction](I-15-Templates and generic programming-T.001.md#Rt-raise) --
[containers](I-15-Templates and generic programming-T.003.md#Rt-cont) --
[concepts](I-15-Templates and generic programming-T.010.md#Rt-concepts)
* `unsigned`:
[and signed](I-10-Expressions and Statements-ES.100.md#Res-mix) --
[bit manipulation](I-10-Expressions and Statements-ES.101.md#Res-unsigned)
* `virtual`:
[interfaces](I-04-Interfaces-I.025.md#Ri-abstract) --
[not `virtual`](I-06-Classes and Class Hierarchies-C.010.md#Rc-concrete) --
[destructor](I-07-Constructors, assignments, and destructors-C.035.md#Rc-dtor-virtual) --
[never fail](I-07-Constructors, assignments, and destructors-C.036.md#Rc-dtor-fail)

You can look at design concepts used to express the rules:

* assertion: ???
* error: ???
* exception: exception guarantee (???)
* failure: ???
* invariant: ???
* leak: ???
* library: ???
* precondition: ???
* postcondition: ???
* resource: ???

