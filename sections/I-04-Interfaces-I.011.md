### <a name="Ri-raw"></a>I.11: Never transfer ownership by a raw pointer (`T*`)

##### Reason

If there is any doubt whether the caller or the callee owns an object, leaks or premature destruction will occur.

##### Example

Consider:

    X* compute(args)    // don't
    {
        X* res = new X{};
        // ...
        return res;
    }

Who deletes the returned `X`? The problem would be harder to spot if compute returned a reference.
Consider returning the result by value (use move semantics if the result is large):

    vector<double> compute(args)  // good
    {
        vector<double> res(10000);
        // ...
        return res;
    }

**Alternative**: [Pass ownership](I-09-Resource%20management-R.030.md#Rr-smartptrparam) using a "smart pointer", such as `unique_ptr` (for exclusive ownership) and `shared_ptr` (for shared ownership).
However, that is less elegant and often less efficient than returning the object itself,
so use smart pointers only if reference semantics are needed.

**Alternative**: Sometimes older code can't be modified because of ABI compatibility requirements or lack of resources.
In that case, mark owning pointers using `owner` from the [guideline support library](I-23-Guideline%20support%20library.md#S-gsl):

    owner<X*> compute(args)    // It is now clear that ownership is transferred
    {
        owner<X*> res = new X{};
        // ...
        return res;
    }

This tells analysis tools that `res` is an owner.
That is, its value must be `delete`d or transferred to another owner, as is done here by the `return`.

`owner` is used similarly in the implementation of resource handles.

##### Note

Every object passed as a raw pointer (or iterator) is assumed to be owned by the
caller, so that its lifetime is handled by the caller. Viewed another way:
ownership transferring APIs are relatively rare compared to pointer-passing APIs,
so the default is "no ownership transfer."

**See also**: [Argument passing](I-05-Functions-F.015.md#Rf-conventional), [use of smart pointer arguments](I-09-Resource%20management-R.030.md#Rr-smartptrparam), and [value return](#Rf-T-return).

##### Enforcement

* (Simple) Warn on `delete` of a raw pointer that is not an `owner<T>`. Suggest use of standard-library resource handle or use of `owner<T>`.
* (Simple) Warn on failure to either `reset` or explicitly `delete` an `owner` pointer on every code path.
* (Simple) Warn if the return value of `new` or a function call with an `owner` return value is assigned to a raw pointer or non-`owner` reference.

