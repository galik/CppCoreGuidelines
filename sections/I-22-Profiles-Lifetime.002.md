### <a name="Pro-lifetime-null-deref"></a>Lifetime.2: Don't dereference a possibly null pointer.

##### Reason

It is undefined behavior.

##### Example, bad

    void f(int* p1)
    {
        *p1 = 42;           // BAD, p1 might be null

        int i = 0;
        int* p2 = condition() ? &i : nullptr;
        *p2 = 42;           // BAD, p2 might be null
    }

##### Example, good

    void f(int* p1, not_null<int*> p3)
    {
        if (p1 != nullptr) {
            *p1 = 42;       // OK, must be not null in this branch
        }

        int i = 0;
        int* p2 = condition() ? &i : nullptr;
        if (p2 != nullptr) {
            *p2 = 42;       // OK, must be not null in this branch
        }

        *p3 = 42;           // OK, not_null does not need to be tested for nullness
    }

##### Enforcement

* Issue a diagnostic for any dereference of a pointer that could have been set to null along a local code path leading to the dereference. To fix: Add a null check and dereference the pointer only in a branch that has tested to ensure non-null.



