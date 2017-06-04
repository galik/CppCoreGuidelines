# <a name="S-introduction"></a>In: Introduction

This is a set of core guidelines for modern C++, C++14, taking likely future enhancements and ISO Technical Specifications (TSs) into account.
The aim is to help C++ programmers to write simpler, more efficient, more maintainable code.

Introduction summary:

* [In.target: Target readership](I-02-Introduction.md#SS-readers)
* [In.aims: Aims](I-02-Introduction.md#SS-aims)
* [In.not: Non-aims](I-02-Introduction-In.000.md#SS-non)
* [In.force: Enforcement](I-02-Introduction-In.000.md#SS-force)
* [In.struct: The structure of this document](I-02-Introduction-In.000.md#SS-struct)
* [In.sec: Major sections](I-02-Introduction-In.000.md#SS-sec)

## <a name="SS-readers"></a>In.target: Target readership

All C++ programmers. This includes [programmers who might consider C](I-16-C-style%20programming.md#S-cpl).

## <a name="SS-aims"></a>In.aims: Aims

The purpose of this document is to help developers to adopt modern C++ (C++11, C++14, and soon C++17) and to achieve a more uniform style across code bases.

We do not suffer the delusion that every one of these rules can be effectively applied to every code base. Upgrading old systems is hard. However, we do believe that a program that uses a rule is less error-prone and more maintainable than one that does not. Often, rules also lead to faster/easier initial development.
As far as we can tell, these rules lead to code that performs as well or better than older, more conventional techniques; they are meant to follow the zero-overhead principle ("what you don't use, you don't pay for" or "when you use an abstraction mechanism appropriately, you get at least as good performance as if you had handcoded using lower-level language constructs").
Consider these rules ideals for new code, opportunities to exploit when working on older code, and try to approximate these ideals as closely as feasible.
Remember:

