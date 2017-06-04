### <a name="Rf-unused"></a>F.9: Unused parameters should be unnamed

##### Reason

Readability.
Suppression of unused parameter warnings.

##### Example

    X* find(map<Blob>& m, const string& s, Hint);   // once upon a time, a hint was used

##### Note

Allowing parameters to be unnamed was introduced in the early 1980 to address this problem.

##### Enforcement

Flag named unused parameters.

## <a name="SS-call"></a>F.call: Parameter passing

There are a variety of ways to pass parameters to a function and to return values.

