### <a name="R0"></a>In.0: Don't panic!

Take the time to understand the implications of a guideline rule on your program.

These guidelines are designed according to the "subset of superset" principle ([Stroustrup05](I-31-Bibliography.md#Stroustrup05)).
They do not simply define a subset of C++ to be used (for reliability, safety, performance, or whatever).
Instead, they strongly recommend the use of a few simple "extensions" ([library components](I-23-Guideline%20support%20library.md#S-gsl))
that make the use of the most error-prone features of C++ redundant, so that they can be banned (in our set of rules).

The rules emphasize static type safety and resource safety.
For that reason, they emphasize possibilities for range checking, for avoiding dereferencing `nullptr`, for avoiding dangling pointers, and the systematic use of exceptions (via RAII).
Partly to achieve that and partly to minimize obscure code as a source of errors, the rules also emphasize simplicity and the hiding of necessary complexity behind well-specified interfaces.

Many of the rules are prescriptive.
We are uncomfortable with rules that simply state "don't do that!" without offering an alternative.
One consequence of that is that some rules can be supported only by heuristics, rather than precise and mechanically verifiable checks.
Other rules articulate general principles. For these more general rules, more detailed and specific rules provide partial checking.

These guidelines address the core of C++ and its use.
We expect that most large organizations, specific application areas, and even large projects will need further rules, possibly further restrictions, and further library support.
For example, hard real-time programmers typically can't use free store (dynamic memory) freely and will be restricted in their choice of libraries.
We encourage the development of such more specific rules as addenda to these core guidelines.
Build your ideal small foundation library and use that, rather than lowering your level of programming to glorified assembly code.

The rules are designed to allow [gradual adoption](I-27-Modernizing%20code.md#S-modernizing).

Some rules aim to increase various forms of safety while others aim to reduce the likelihood of accidents, many do both.
The guidelines aimed at preventing accidents often ban perfectly legal C++.
However, when there are two ways of expressing an idea and one has shown itself a common source of errors and the other has not, we try to guide programmers towards the latter.

## <a name="SS-non"></a>In.not: Non-aims

The rules are not intended to be minimal or orthogonal.
In particular, general rules can be simple, but unenforceable.
Also, it is often hard to understand the implications of a general rule.
More specialized rules are often easier to understand and to enforce, but without general rules, they would just be a long list of special cases.
We provide rules aimed at helping novices as well as rules supporting expert use.
Some rules can be completely enforced, but others are based on heuristics.

These rules are not meant to be read serially, like a book.
You can browse through them using the links.
However, their main intended use is to be targets for tools.
That is, a tool looks for violations and the tool returns links to violated rules.
The rules then provide reasons, examples of potential consequences of the violation, and suggested remedies.

These guidelines are not intended to be a substitute for a tutorial treatment of C++.
If you need a tutorial for some given level of experience, see [the references](I-21-References.md#S-references).

This is not a guide on how to convert old C++ code to more modern code.
It is meant to articulate ideas for new code in a concrete fashion.
However, see [the modernization section](I-27-Modernizing%20code.md#S-modernizing) for some possible approaches to modernizing/rejuvenating/upgrading.
Importantly, the rules support gradual adoption: It is typically infeasible to completely convert a large code base all at once.

These guidelines are not meant to be complete or exact in every language-technical detail.
For the final word on language definition issues, including every exception to general rules and every feature, see the ISO C++ standard.

The rules are not intended to force you to write in an impoverished subset of C++.
They are *emphatically* not meant to define a, say, Java-like subset of C++.
They are not meant to define a single "one true C++" language.
We value expressiveness and uncompromised performance.

The rules are not value-neutral.
They are meant to make code simpler and more correct/safer than most existing C++ code, without loss of performance.
They are meant to inhibit perfectly valid C++ code that correlates with errors, spurious complexity, and poor performance.

The rules are not perfect.
A rule can do harm by prohibiting something that is useful in a given situation.
A rule can do harm by failing to prohibit something that enables a serious error in a given situation.
A rule can do a lot of harm by being vague, ambiguous, unenforceable, or by enabling every solution to a problem.
It is impossible to completely meet the "do no harm" criteria.
Instead, our aim is the less ambitious: "Do the most good for most programmers";
if you cannot live with a rule, object to it, ignore it, but don't water it down until it becomes meaningless.
Also, suggest an improvement.

## <a name="SS-force"></a>In.force: Enforcement

Rules with no enforcement are unmanageable for large code bases.
Enforcement of all rules is possible only for a small weak set of rules or for a specific user community.

* But we want lots of rules, and we want rules that everybody can use.
* But different people have different needs.
* But people don't like to read lots of rules.
* But people can't remember many rules.

So, we need subsetting to meet a variety of needs.

* But arbitrary subsetting leads to chaos.

We want guidelines that help a lot of people, make code more uniform, and strongly encourage people to modernize their code.
We want to encourage best practices, rather than leave all to individual choices and management pressures.
The ideal is to use all rules; that gives the greatest benefits.

This adds up to quite a few dilemmas.
We try to resolve those using tools.
Each rule has an **Enforcement** section listing ideas for enforcement.
Enforcement might be done by code review, by static analysis, by compiler, or by run-time checks.
Wherever possible, we prefer "mechanical" checking (humans are slow, inaccurate, and bore easily) and static checking.
Run-time checks are suggested only rarely where no alternative exists; we do not want to introduce "distributed fat".
Where appropriate, we label a rule (in the **Enforcement** sections) with the name of groups of related rules (called "profiles").
A rule can be part of several profiles, or none.
For a start, we have a few profiles corresponding to common needs (desires, ideals):

* **type**: No type violations (reinterpreting a `T` as a `U` through casts, unions, or varargs)
* **bounds**: No bounds violations (accessing beyond the range of an array)
* **lifetime**: No leaks (failing to `delete` or multiple `delete`) and no access to invalid objects (dereferencing `nullptr`, using a dangling reference).

The profiles are intended to be used by tools, but also serve as an aid to the human reader.
We do not limit our comment in the **Enforcement** sections to things we know how to enforce; some comments are mere wishes that might inspire some tool builder.

Tools that implement these rules shall respect the following syntax to explicitly suppress a rule:

```cpp
[[gsl::suppress(tag)]]

```
where "tag" is the anchor name of the item where the Enforcement rule appears (e.g., for [C.134](I-07-Constructors%2C%20assignments%2C%20and%20destructors-C.134.md#Rh-public) it is "Rh-public"), the
name of a profile group-of-rules ("type", "bounds", or "lifetime"),
or a specific rule in a profile ([type.4](I-22-Profiles.md#Pro-type-cstylecast), or [bounds.2](#Pro-bounds-arrayindex)).

## <a name="SS-struct"></a>In.struct: The structure of this document

Each rule (guideline, suggestion) can have several parts:

* The rule itself -- e.g., **no naked `new`**
* A rule reference number -- e.g., **C.7** (the 7th rule related to classes).
  Since the major sections are not inherently ordered, we use letters as the first part of a rule reference "number".
  We leave gaps in the numbering to minimize "disruption" when we add or remove rules.
* **Reason**s (rationales) -- because programmers find it hard to follow rules they don't understand
* **Example**s -- because rules are hard to understand in the abstract; can be positive or negative
* **Alternative**s -- for "don't do this" rules
* **Exception**s -- we prefer simple general rules. However, many rules apply widely, but not universally, so exceptions must be listed
* **Enforcement** -- ideas about how the rule might be checked "mechanically"
* **See also**s -- references to related rules and/or further discussion (in this document or elsewhere)
* **Note**s (comments) -- something that needs saying that doesn't fit the other classifications
* **Discussion** -- references to more extensive rationale and/or examples placed outside the main lists of rules

Some rules are hard to check mechanically, but they all meet the minimal criteria that an expert programmer can spot many violations without too much trouble.
We hope that "mechanical" tools will improve with time to approximate what such an expert programmer notices.
Also, we assume that the rules will be refined over time to make them more precise and checkable.

A rule is aimed at being simple, rather than carefully phrased to mention every alternative and special case.
Such information is found in the **Alternative** paragraphs and the [Discussion](I-28-Discussion.md#S-discussion) sections.
If you don't understand a rule or disagree with it, please visit its **Discussion**.
If you feel that a discussion is missing or incomplete, enter an [Issue](https://github.com/isocpp/CppCoreGuidelines/issues)
explaining your concerns and possibly a corresponding PR.

This is not a language manual.
It is meant to be helpful, rather than complete, fully accurate on technical details, or a guide to existing code.
Recommended information sources can be found in [the references](I-21-References.md#S-references).

## <a name="SS-sec"></a>In.sec: Major sections

* [In: Introduction](I-02-Introduction.md#S-introduction)
* [P: Philosophy](I-03-Philosophy.md#S-philosophy)
* [I: Interfaces](I-04-Interfaces.md#S-interfaces)
* [F: Functions](I-05-Functions.md#S-functions)
* [C: Classes and class hierarchies](I-06-Classes%20and%20Class%20Hierarchies.md#S-class)
* [Enum: Enumerations](I-08-Enumerations.md#S-enum)
* [R: Resource management](I-09-Resource%20management.md#S-resource)
* [ES: Expressions and statements](I-10-Expressions%20and%20Statements.md#S-expr)
* [E: Error handling](I-13-Error%20handling.md#S-errors)
* [Con: Constants and immutability](I-14-Constants%20and%20Immutability.md#S-const)
* [T: Templates and generic programming](I-15-Templates%20and%20generic%20programming.md#S-templates)
* [CP: Concurrency](I-12-Concurrency%20and%20Parallelism.md#S-concurrency)
* [SL: The Standard library](I-18-The%20Standard%20Library.md#S-stdlib)
* [SF: Source files](I-17-Source%20files.md#S-source)
* [CPL: C-style programming](I-16-C-style%20programming.md#S-cpl)
* [Pro: Profiles](I-22-Profiles.md#S-profile)
* [GSL: Guideline support library](I-23-Guideline%20support%20library.md#S-gsl)
* [FAQ: Answers to frequently asked questions](I-25-Answers%20to%20frequently%20asked%20questions.md#S-faq)

Supporting sections:

* [NL: Naming and layout](I-24-Naming%20and%20layout%20rules.md#S-naming)
* [Per: Performance](I-11-Performance.md#S-performance)
* [N: Non-Rules and myths](I-20-Non-Rules%20and%20myths.md#S-not)
* [RF: References](I-21-References.md#S-references)
* [Appendix A: Libraries](I-26-Libraries.md#S-libraries)
* [Appendix B: Modernizing code](I-27-Modernizing%20code.md#S-modernizing)
* [Appendix C: Discussion](I-28-Discussion.md#S-discussion)
* [Glossary](I-29-Glossary.md#S-glossary)
* [To-do: Unclassified proto-rules](I-30-Unclassified%20proto-rules.md#S-unclassified)

These sections are not orthogonal.

Each section (e.g., "P" for "Philosophy") and each subsection (e.g., "C.hier" for "Class Hierarchies (OOP)") have an abbreviation for ease of searching and reference.
The main section abbreviations are also used in rule numbers (e.g., "C.11" for "Make concrete types regular").

