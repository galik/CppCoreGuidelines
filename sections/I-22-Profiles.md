# <a name="S-profile"></a>Pro: Profiles

Ideally, we would follow all of the guidelines.
That would give the cleanest, most regular, least error-prone, and often the fastest code.
Unfortunately, that is usually impossible because we have to fit our code into large code bases and use existing libraries.
Often, such code has been written over decades and does not follow these guidelines.
We must aim for [gradual adoption](I-27-Modernizing%20code.md#S-modernizing).

Whatever strategy for gradual adoption we adopt, we need to be able to apply sets of related guidelines to address some set
of problems first and leave the rest until later.
A similar idea of "related guidelines" becomes important when some, but not all, guidelines are considered relevant to a code base
or if a set of specialized guidelines is to be applied for a specialized application area.
We call such a set of related guidelines a "profile".
We aim for such a set of guidelines to be coherent so that they together help us reach a specific goal, such as "absence of range errors"
or "static type safety."
Each profile is designed to eliminate a class of errors.
Enforcement of "random" rules in isolation is more likely to be disruptive to a code base than delivering a definite improvement.

A "profile" is a set of deterministic and portably enforceable subset rules (i.e., restrictions) that are designed to achieve a specific guarantee.
"Deterministic" means they require only local analysis and could be implemented in a compiler (though they don't need to be).
"Portably enforceable" means they are like language rules, so programmers can count on different enforcement tools giving the same answer for the same code.

Code written to be warning-free using such a language profile is considered to conform to the profile.
Conforming code is considered to be safe by construction with regard to the safety properties targeted by that profile.
Conforming code will not be the root cause of errors for that property,
although such errors may be introduced into a program by other code, libraries or the external environment.
A profile may also introduce additional library types to ease conformance and encourage correct code.

Profiles summary:

* [Pro.type: Type safety](I-22-Profiles.md#SS-type)
* [Pro.bounds: Bounds safety](I-22-Profiles.md#SS-bounds)
* [Pro.lifetime: Lifetime safety](I-22-Profiles.md#SS-lifetime)

In the future, we expect to define many more profiles and add more checks to existing profiles.
Candidates include:

* narrowing arithmetic promotions/conversions (likely part of a separate safe-arithmetic profile)
* arithmetic cast from negative floating point to unsigned integral type (ditto)
* selected undefined behavior: Start with Gabriel Dos Reis's UB list developed for the WG21 study group
* selected unspecified behavior: Addressing portability concerns.
* `const` violations: Mostly done by compilers already, but we can catch inappropriate casting and underuse of `const`.

Enabling a profile is implementation defined; typically, it is set in the analysis tool used.

To suppress enforcement of a profile check, place a `suppress` annotation on a language contract. For example:

```cpp
[[suppress(bounds)]] char* raw_find(char* p, int n, char x)    // find x in p[0]..p[n-1]
{
    // ...
}

```
Now `raw_find()` can scramble memory to its heart's content.
Obviously, suppression should be very rare.

## <a name="SS-type"></a>Pro.safety: Type-safety profile

This profile makes it easier to construct code that uses types correctly and avoids inadvertent type punning.
It does so by focusing on removing the primary sources of type violations, including unsafe uses of casts and unions.

For the purposes of this section,
type-safety is defined to be the property that a variable is not used in a way that doesn't obey the rules for the type of its definition.
Memory accessed as a type `T` should not be valid memory that actually contains an object of an unrelated type `U`.
Note that the safety is intended to be complete when combined also with [Bounds safety](I-22-Profiles.md#SS-bounds) and [Lifetime safety](I-22-Profiles.md#SS-lifetime).

An implementation of this profile shall recognize the following patterns in source code as non-conforming and issue a diagnostic.

Type safety profile summary:

* <a name="Pro-type-reinterpretcast"></a>Type.1: Don't use `reinterpret_cast`:
A strict version of [Avoid casts](I-10-Expressions%20and%20Statements-ES.048.md#Res-casts) and [prefer named casts](I-10-Expressions%20and%20Statements-ES.049.md#Res-casts-named).
* <a name="Pro-type-downcast"></a>Type.2: Don't use `static_cast` to downcast:
[Use `dynamic_cast` instead](I-07-Constructors%2C%20assignments%2C%20and%20destructors-C.146.md#Rh-dynamic_cast).
* <a name="Pro-type-constcast"></a>Type.3: Don't use `const_cast` to cast away `const` (i.e., at all):
[Don't cast away const](I-10-Expressions%20and%20Statements-ES.050.md#Res-casts-const).
* <a name="Pro-type-cstylecast"></a>Type.4: Don't use C-style `(T)expression` or functional `T(expression)` casts:
Prefer [construction](I-10-Expressions%20and%20Statements-ES.064.md#Res-construct) or [named casts](#Res-cast-named).
* <a name="Pro-type-init"></a>Type.5: Don't use a variable before it has been initialized:
[always initialize](I-10-Expressions%20and%20Statements-ES.020.md#Res-always).
* <a name="Pro-type-memberinit"></a>Type.6: Always initialize a member variable:
[always initialize](I-10-Expressions%20and%20Statements-ES.020.md#Res-always),
possibly using [default constructors](I-07-Constructors%2C%20assignments%2C%20and%20destructors-C.043.md#Rc-default0) or
[default member initializers](#Rc-in-class-initializers).
* <a name="Pro-type-unon"></a>Type.7: Avoid naked union:
[Use `variant` instead](I-07-Constructors%2C%20assignments%2C%20and%20destructors-C.181.md#Ru-naked).
* <a name="Pro-type-varargs"></a>Type.8: Avoid varargs:
[Don't use `va_arg` arguments](I-05-Functions-F.055.md#F-varargs).

##### Impact

With the type-safety profile you can trust that every operation is applied to a valid object.
Exception may be thrown to indicate errors that cannot be detected statically (at compile time).
Note that this type-safety can be complete only if we also have [Bounds safety](I-22-Profiles.md#SS-bounds) and [Lifetime safety](I-22-Profiles.md#SS-lifetime).
Without those guarantees, a region of memory could be accessed independent of which object, objects, or parts of objects are stored in it.


## <a name="SS-bounds"></a>Pro.bounds: Bounds safety profile

This profile makes it easier to construct code that operates within the bounds of allocated blocks of memory.
It does so by focusing on removing the primary sources of bounds violations: pointer arithmetic and array indexing.
One of the core features of this profile is to restrict pointers to only refer to single objects, not arrays.

We define bounds-safety to be the property that a program does not use an object to access memory outside of the range that was allocated for it.
Bounds safety is intended to be complete only when combined with [Type safety](I-22-Profiles.md#SS-type) and [Lifetime safety](I-22-Profiles.md#SS-lifetime),
which cover other unsafe operations that allow bounds violations.

Bounds safety profile summary:

* <a href="Pro-bounds-arithmetic"></a>Bounds.1: Don't use pointer arithmetic. Use `span` instead:
[Pass pointers to single objects (only)](I-04-Interfaces-I.013.md#Ri-array) and [Keep pointer arithmetic simple](#Res-simple).
* <a href="Pro-bounds-arrayindex"></a>Bounds.2: Only index into arrays using constant expressions:
[Pass pointers to single objects (only)](I-04-Interfaces-I.013.md#Ri-array) and [Keep pointer arithmetic simple](#Res-simple).
* <a href="Pro-bounds-decay"></a>Bounds.3: No array-to-pointer decay:
[Pass pointers to single objects (only)](I-04-Interfaces-I.013.md#Ri-array) and [Keep pointer arithmetic simple](#Res-simple).
* <a href="Pro-bounds-stdlib"></a>Bounds.4: Don't use standard library functions and types that are not bounds-checked:
[Use the standard library in a type-safe manner](I-18-The%20Standard%20Library-SL.con.003.md#Rsl-bounds).

##### Impact

Bounds safety implies that access to an object - notably arrays - does not access beyond the object's memory allocation.
This eliminates a large class of insidious and hard-to-find errors, including the (in)famous "buffer overflow" errors.
This closes security loopholes as well as a prominent source of memory corruption (when writing out of bounds).
Even an out-of-bounds access is "just a read", it can lead to invariant violations (when the accessed isn't of the assumed type)
and "mysterious values."


## <a name="SS-lifetime"></a>Pro.lifetime: Lifetime safety profile

See /docs folder for the initial design. The detailed formal rules are in progress (as of May 2017).

The following are specific rules that are being enforced.

Lifetime safety profile summary:

* [Lifetime.1: Don't dereference a possibly invalid pointer.](I-22-Profiles-Lifetime.001.md#Pro-lifetime-invalid-deref)
* [Lifetime.2: Don't dereference a possibly null pointer.](I-22-Profiles-Lifetime.002.md#Pro-lifetime-null-deref)
* [Lifetime.3: Don't pass a possibly invalid pointer to a function.](I-22-Profiles-Lifetime.003.md#Pro-lifetime-invalid-argument)

??? These rules will be moved into the main-line sections of these guidelines ???

