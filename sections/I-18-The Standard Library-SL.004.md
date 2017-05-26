### <a name="sl-safe"></a>SL.4: Use the standard library in a type-safe manner

##### Reason

Because, obviously, breaking this rule can lead to undefined behavior, memory corruption, and all kinds of other bad errors.

##### Note

This is a semi-philosophical meta-rule, which needs many supporting concrete rules.
We need it as a umbrella for the more specific rules.

Summary of more specific rules:

* [SL.4: Use the standard library in a type-safe manner](I-18-The Standard Library-SL.004.md#sl-safe)


## <a name="SS-con"></a>SL.con: Containers

???

Container rule summary:

* [SL.con.1: Prefer using STL `array` or `vector` instead of a C array](I-18-The Standard Library-SL.con.001.md#Rsl-arrays)
* [SL.con.2: Prefer using STL `vector` by default unless you have a reason to use a different container](I-18-The Standard Library-SL.con.002.md#Rsl-vector)
* [SL.con.3: Avoid bounds errors](I-18-The Standard Library-SL.con.003.md#Rsl-bounds)
*  ???

