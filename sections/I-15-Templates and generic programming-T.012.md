### <a name="Rt-auto"></a>T.12: Prefer concept names over `auto` for local variables

##### Reason

 `auto` is the weakest concept. Concept names convey more meaning than just `auto`.

##### Example (using TS concepts)

    vector<string> v;
    auto& x = v.front();     // bad
    String& s = v.begin();   // good (String is a GSL concept)

##### Enforcement

* ???

