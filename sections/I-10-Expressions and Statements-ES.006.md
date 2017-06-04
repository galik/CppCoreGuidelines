### <a name="Res-cond"></a>ES.6: Declare names in for-statement initializers and conditions to limit scope

##### Reason

Readability. Minimize resource retention.

##### Example

    void use()
    {
        for (string s; cin >> s;)
            v.push_back(s);

        for (int i = 0; i < 20; ++i) {   // good: i is local to for-loop
            // ...
        }

        if (auto pc = dynamic_cast<Circle*>(ps)) {   // good: pc is local to if-statement
            // ... deal with Circle ...
        }
        else {
            // ... handle error ...
        }
    }

##### Enforcement

* Flag loop variables declared before the loop and not used after the loop
* (hard) Flag loop variables declared before the loop and used after the loop for an unrelated purpose.

##### C++17 example

Note: C++17 also adds `if` and `switch` initializer statements. These require C++17 support.

    map<int, string> mymap;

    if (auto result = mymap.insert(value); result.second) {
        // insert succeeded, and result is valid for this block
        use(result.first);  // ok
        // ...
    } // result is destroyed here

##### C++17 enforcement (if using a C++17 compiler)

* Flag selection/loop variables declared before the body and not used after the body
* (hard) Flag selection/loop variables declared before the body and used after the body for an unrelated purpose.



