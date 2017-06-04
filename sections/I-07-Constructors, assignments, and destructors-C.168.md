### <a name="Ro-namespace"></a>C.168: Define overloaded operators in the namespace of their operands

##### Reason

Readability.
Ability for find operators using ADL.
Avoiding inconsistent definition in different namespaces

##### Example

    struct S { };
    bool operator==(S, S);   // OK: in the same namespace as S, and even next to S
    S s;

    bool x = (s == s);

This is what a default `==` would do, if we had such defaults.

##### Example

    namespace N {
        struct S { };
        bool operator==(S, S);   // OK: in the same namespace as S, and even next to S
    }

    N::S s;

    bool x = (s == s);  // finds N::operator==() by ADL

##### Example, bad

    struct S { };
    S s;

    namespace N {
        S::operator!(S a) { return true; }
        S not_s = !s;
    }

    namespace M {
        S::operator!(S a) { return false; }
        S not_s = !s;
    }

Here, the meaning of `!s` differs in `N` and `M`.
This can be most confusing.
Remove the definition of `namespace M` and the confusion is replaced by an opportunity to make the mistake.

##### Note

If a binary operator is defined for two types that are defined in different namespaces, you cannot follow this rule.
For example:

    Vec::Vector operator*(const Vec::Vector&, const Mat::Matrix&);

This may be something best avoided.

##### See also

This is a special case of the rule that [helper functions should be defined in the same namespace as their class](I-06-Classes%20and%20Class%20Hierarchies-C.005.md#Rc-helper).

##### Enforcement

* Flag operator definitions that are not it the namespace of their operands

