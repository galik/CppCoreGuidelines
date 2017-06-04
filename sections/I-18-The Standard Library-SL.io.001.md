### <a name="Rio-low"></a>SL.io.1: Use character-level input only when you have to

##### Reason

Unless you genuinely just deal with individual characters, using character-level input leads to the user code performing potentially error-prone
and potentially inefficient composition of tokens out of characters.

##### Example

    char c;
    char buf[128];
    int i = 0;
    while (cin.get(c) && !isspace(c) && i < 128)
        buf[i++] = c;
    if (i == 128) {
        // ... handle too long string ....
    }

Better (much simpler and probably faster):

    string s;
    s.reserve(128);
    cin >> s;

and the `reserve(128)` is probably not worthwhile.

##### Enforcement

???


