# <a name="main"></a>C++ Core Guidelines

JUne 3, 2017


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
When commenting, please note [the introduction](S-02-Introduction.md#S-introduction) that outlines our aims and general approach.
The list of contributors is [here](S-21-References.md#SS-ack).

Problems:

* The sets of rules have not been thoroughly checked for completeness, consistency, or enforceability.
* Triple question marks (???) mark known missing information
* Update reference sections; many pre-C++11 sources are too old.
* For a more-or-less up-to-date to-do list see: [To-do: Unclassified proto-rules](S-30-Unclassified%20proto-rules.md#S-unclassified)

You can [read an explanation of the scope and structure of this Guide](S-01-Abstract.md#S-abstract) or just jump straight in:

* [In: Introduction](S-02-Introduction.md#S-introduction)
* [P: Philosophy](S-03-Philosophy.md#S-philosophy)
* [I: Interfaces](S-04-Interfaces.md#S-interfaces)
* [F: Functions](S-05-Functions.md#S-functions)
* [C: Classes and class hierarchies](S-06-Classes%20and%20Class%20Hierarchies.md#S-class)
* [Enum: Enumerations](S-08-Enumerations.md#S-enum)
* [R: Resource management](S-09-Resource%20management.md#S-resource)
* [ES: Expressions and statements](S-10-Expressions%20and%20Statements.md#S-expr)
* [Per: Performance](S-11-Performance.md#S-performance)
* [CP: Concurrency](S-12-Concurrency%20and%20Parallelism.md#S-concurrency)
* [E: Error handling](S-13-Error%20handling.md#S-errors)
* [Con: Constants and immutability](S-14-Constants%20and%20Immutability.md#S-const)
* [T: Templates and generic programming](S-15-Templates%20and%20generic%20programming.md#S-templates)
* [CPL: C-style programming](S-16-C-style%20programming.md#S-cpl)
* [SF: Source files](S-17-Source%20files.md#S-source)
* [SL: The Standard library](S-18-The%20Standard%20Library.md#S-stdlib)

Supporting sections:

* [A: Architectural Ideas](S-19-Architectural%20Ideas.md#S-A)
* [N: Non-Rules and myths](S-20-Non-Rules%20and%20myths.md#S-not)
* [RF: References](S-21-References.md#S-references)
* [Pro: Profiles](S-22-Profiles.md#S-profile)
* [GSL: Guideline support library](S-23-Guideline%20support%20library.md#S-gsl)
* [NL: Naming and layout](S-24-Naming%20and%20layout%20rules.md#S-naming)
* [FAQ: Answers to frequently asked questions](S-25-Answers%20to%20frequently%20asked%20questions.md#S-faq)
* [Appendix A: Libraries](S-26-Libraries.md#S-libraries)
* [Appendix B: Modernizing code](S-27-Modernizing%20code.md#S-modernizing)
* [Appendix C: Discussion](S-28-Discussion.md#S-discussion)
* [Glossary](S-29-Glossary.md#S-glossary)
* [To-do: Unclassified proto-rules](S-30-Unclassified%20proto-rules.md#S-unclassified)

You can sample rules for specific language features:

* assignment:
[regular types](S-06-Classes%20and%20Class%20Hierarchies.md#Rc-regular) --
[prefer initialization](S-07-Constructors%2C%20assignments%2C%20and%20destructors.md#Rc-initialize) --
[copy](#Rc-copy-semantics) --
[move](#Rc-move-semantics) --
[other operations](S-07-Constructors%2C%20assignments%2C%20and%20destructors.md#Rc-matched) --
[default](S-07-Constructors%2C%20assignments%2C%20and%20destructors.md#Rc-eqdefault)
* `class`:
[data](S-06-Classes%20and%20Class%20Hierarchies.md#Rc-org) --
[invariant](S-06-Classes%20and%20Class%20Hierarchies.md#Rc-struct) --
[members](S-06-Classes%20and%20Class%20Hierarchies.md#Rc-member) --
[helpers](S-06-Classes%20and%20Class%20Hierarchies.md#Rc-helper) --
[concrete types](S-06-Classes%20and%20Class%20Hierarchies.md#SS-concrete) --
[ctors, =, and dtors](S-07-Constructors%2C%20assignments%2C%20and%20destructors.md#S-ctor) --
[hierarchy](S-07-Constructors%2C%20assignments%2C%20and%20destructors.md#SS-hier) --
[operators](S-07-Constructors%2C%20assignments%2C%20and%20destructors.md#SS-overload)
* `concept`:
[rules](S-15-Templates%20and%20generic%20programming.md#SS-concepts) --
[in generic programming](S-15-Templates%20and%20generic%20programming.md#Rt-raise) --
[template arguments](#RT-concepts) --
[semantics](S-15-Templates%20and%20generic%20programming.md#Rt-low)
* constructor:
[invariant](S-06-Classes%20and%20Class%20Hierarchies.md#Rc-struct) --
[establish invariant](S-07-Constructors%2C%20assignments%2C%20and%20destructors.md#Rc-ctor) --
[`throw`](S-07-Constructors%2C%20assignments%2C%20and%20destructors.md#Rc-throw) --
[default](S-07-Constructors%2C%20assignments%2C%20and%20destructors.md#Rc-default0) --
[not needed](S-07-Constructors%2C%20assignments%2C%20and%20destructors.md#Rc-default) --
[`explicit`](S-07-Constructors%2C%20assignments%2C%20and%20destructors.md#Rc-explicit) --
[delegating](S-07-Constructors%2C%20assignments%2C%20and%20destructors.md#Rc-delegating) --
[`virtual`](#RC-ctor-virtual)
* derived `class`:
[when to use](S-07-Constructors%2C%20assignments%2C%20and%20destructors.md#Rh-domain) --
[as interface](S-07-Constructors%2C%20assignments%2C%20and%20destructors.md#Rh-abstract) --
[destructors](S-07-Constructors%2C%20assignments%2C%20and%20destructors.md#Rh-dtor) --
[copy](S-07-Constructors%2C%20assignments%2C%20and%20destructors.md#Rh-copy) --
[getters and setters](S-07-Constructors%2C%20assignments%2C%20and%20destructors.md#Rh-get) --
[multiple inheritance](S-07-Constructors%2C%20assignments%2C%20and%20destructors.md#Rh-mi-interface) --
[overloading](S-07-Constructors%2C%20assignments%2C%20and%20destructors.md#Rh-using) --
[slicing](S-07-Constructors%2C%20assignments%2C%20and%20destructors.md#Rc-copy-virtual) --
[`dynamic_cast`](S-07-Constructors%2C%20assignments%2C%20and%20destructors.md#Rh-dynamic_cast)
* destructor:
[and constructors](S-07-Constructors%2C%20assignments%2C%20and%20destructors.md#Rc-matched) --
[when needed?](S-07-Constructors%2C%20assignments%2C%20and%20destructors.md#Rc-dtor) --
[may not fail](S-07-Constructors%2C%20assignments%2C%20and%20destructors.md#Rc-dtor-fail)
* exception:
[errors](S-13-Error%20handling.md#S-errors) --
[`throw`](S-13-Error%20handling.md#Re-throw) --
[for errors only](S-13-Error%20handling.md#Re-errors) --
[`noexcept`](S-13-Error%20handling.md#Re-noexcept) --
[minimize `try`](S-13-Error%20handling.md#Re-catch) --
[what if no exceptions?](S-13-Error%20handling.md#Re-no-throw-codes)
* `for`:
[range-for and for](S-10-Expressions%20and%20Statements.md#Res-for-range) --
[for and while](S-10-Expressions%20and%20Statements.md#Res-for-while) --
[for-initializer](S-10-Expressions%20and%20Statements.md#Res-for-init) --
[empty body](S-10-Expressions%20and%20Statements.md#Res-empty) --
[loop variable](S-10-Expressions%20and%20Statements.md#Res-loop-counter) --
[loop variable type ???](#Res-???)
* function:
[naming](S-05-Functions.md#Rf-package) --
[single operation](S-05-Functions.md#Rf-logical) --
[no throw](S-05-Functions.md#Rf-noexcept) --
[arguments](S-05-Functions.md#Rf-smart) --
[argument passing](S-05-Functions.md#Rf-conventional) --
[multiple return values](S-05-Functions.md#Rf-out-multi) --
[pointers](S-05-Functions.md#Rf-return-ptr) --
[lambdas](S-05-Functions.md#Rf-capture-vs-overload)
* `inline`:
[small functions](S-05-Functions.md#Rf-inline) --
[in headers](S-17-Source%20files.md#Rs-inline)
* initialization:
[always](S-10-Expressions%20and%20Statements.md#Res-always) --
[prefer `{}`](S-10-Expressions%20and%20Statements.md#Res-list) --
[lambdas](S-10-Expressions%20and%20Statements.md#Res-lambda-init) --
[in-class initializers](S-07-Constructors%2C%20assignments%2C%20and%20destructors.md#Rc-in-class-initializer) --
[class members](S-07-Constructors%2C%20assignments%2C%20and%20destructors.md#Rc-initialize) --
[factory functions](S-07-Constructors%2C%20assignments%2C%20and%20destructors.md#Rc-factory)
* lambda expression:
[when to use](S-07-Constructors%2C%20assignments%2C%20and%20destructors.md#SS-lambdas)
* operator:
[conventional](S-07-Constructors%2C%20assignments%2C%20and%20destructors.md#Ro-conventional) --
[avoid conversion operators](S-07-Constructors%2C%20assignments%2C%20and%20destructors.md#Ro-conventional) --
[and lambdas](S-07-Constructors%2C%20assignments%2C%20and%20destructors.md#Ro-lambda)
* `public`, `private`, and `protected`:
[information hiding](S-06-Classes%20and%20Class%20Hierarchies.md#Rc-private) --
[consistency](S-07-Constructors%2C%20assignments%2C%20and%20destructors.md#Rh-public) --
[`protected`](S-07-Constructors%2C%20assignments%2C%20and%20destructors.md#Rh-protected)
* `static_assert`:
[compile-time checking](S-03-Philosophy.md#Rp-compile-time) --
[and concepts](S-15-Templates%20and%20generic%20programming.md#Rt-check-class)
* `struct`:
[for organizing data](S-06-Classes%20and%20Class%20Hierarchies.md#Rc-org) --
[use if no invariant](S-06-Classes%20and%20Class%20Hierarchies.md#Rc-struct) --
[no private members](S-06-Classes%20and%20Class%20Hierarchies.md#Rc-class)
* `template`:
[abstraction](S-15-Templates%20and%20generic%20programming.md#Rt-raise) --
[containers](S-15-Templates%20and%20generic%20programming.md#Rt-cont) --
[concepts](S-15-Templates%20and%20generic%20programming.md#Rt-concepts)
* `unsigned`:
[and signed](S-10-Expressions%20and%20Statements.md#Res-mix) --
[bit manipulation](S-10-Expressions%20and%20Statements.md#Res-unsigned)
* `virtual`:
[interfaces](S-04-Interfaces.md#Ri-abstract) --
[not `virtual`](S-06-Classes%20and%20Class%20Hierarchies.md#Rc-concrete) --
[destructor](S-07-Constructors%2C%20assignments%2C%20and%20destructors.md#Rc-dtor-virtual) --
[never fail](S-07-Constructors%2C%20assignments%2C%20and%20destructors.md#Rc-dtor-fail)

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

