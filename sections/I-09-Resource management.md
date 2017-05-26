# <a name="S-resource"></a>R: Resource management

This section contains rules related to resources.
A resource is anything that must be acquired and (explicitly or implicitly) released, such as memory, file handles, sockets, and locks.
The reason it must be released is typically that it can be in short supply, so even delayed release may do harm.
The fundamental aim is to ensure that we don't leak any resources and that we don't hold a resource longer than we need to.
An entity that is responsible for releasing a resource is called an owner.

There are a few cases where leaks can be acceptable or even optimal:
If you are writing a program that simply produces an output based on an input and the amount of memory needed is proportional to the size of the input, the optimal strategy (for performance and ease of programming) is sometimes simply never to delete anything.
If you have enough memory to handle your largest input, leak away, but be sure to give a good error message if you are wrong.
Here, we ignore such cases.

* Resource management rule summary:

  * [R.1: Manage resources automatically using resource handles and RAII (Resource Acquisition Is Initialization)](I-09-Resource%20management-R.001.md#Rr-raii)
  * [R.2: In interfaces, use raw pointers to denote individual objects (only)](I-09-Resource%20management-R.002.md#Rr-use-ptr)
  * [R.3: A raw pointer (a `T*`) is non-owning](I-09-Resource%20management-R.003.md#Rr-ptr)
  * [R.4: A raw reference (a `T&`) is non-owning](I-09-Resource%20management-R.004.md#Rr-ref)
  * [R.5: Prefer scoped objects, don't heap-allocate unnecessarily](I-09-Resource%20management-R.005.md#Rr-scoped)
  * [R.6: Avoid non-`const` global variables](I-09-Resource%20management-R.006.md#Rr-global)

* Allocation and deallocation rule summary:

  * [R.10: Avoid `malloc()` and `free()`](I-09-Resource%20management-R.010.md#Rr-mallocfree)
  * [R.11: Avoid calling `new` and `delete` explicitly](I-09-Resource%20management-R.011.md#Rr-newdelete)
  * [R.12: Immediately give the result of an explicit resource allocation to a manager object](I-09-Resource%20management-R.012.md#Rr-immediate-alloc)
  * [R.13: Perform at most one explicit resource allocation in a single expression statement](I-09-Resource%20management-R.013.md#Rr-single-alloc)
  * [R.14: ??? array vs. pointer parameter](I-09-Resource%20management-R.014.md#Rr-ap)
  * [R.15: Always overload matched allocation/deallocation pairs](I-09-Resource%20management-R.015.md#Rr-pair)

* <a name="Rr-summary-smartptrs"></a>Smart pointer rule summary:

  * [R.20: Use `unique_ptr` or `shared_ptr` to represent ownership](I-09-Resource%20management-R.020.md#Rr-owner)
  * [R.21: Prefer `unique_ptr` over `shared_ptr` unless you need to share ownership](I-09-Resource%20management-R.021.md#Rr-unique)
  * [R.22: Use `make_shared()` to make `shared_ptr`s](I-09-Resource%20management-R.022.md#Rr-make_shared)
  * [R.23: Use `make_unique()` to make `unique_ptr`s](I-09-Resource%20management-R.023.md#Rr-make_unique)
  * [R.24: Use `std::weak_ptr` to break cycles of `shared_ptr`s](I-09-Resource%20management-R.024.md#Rr-weak_ptr)
  * [R.30: Take smart pointers as parameters only to explicitly express lifetime semantics](I-09-Resource%20management-R.030.md#Rr-smartptrparam)
  * [R.31: If you have non-`std` smart pointers, follow the basic pattern from `std`](I-09-Resource%20management-R.031.md#Rr-smart)
  * [R.32: Take a `unique_ptr<widget>` parameter to express that a function assumes ownership of a `widget`](I-09-Resource%20management-R.032.md#Rr-uniqueptrparam)
  * [R.33: Take a `unique_ptr<widget>&` parameter to express that a function reseats the `widget`](I-09-Resource%20management-R.033.md#Rr-reseat)
  * [R.34: Take a `shared_ptr<widget>` parameter to express that a function is part owner](I-09-Resource%20management-R.034.md#Rr-sharedptrparam-owner)
  * [R.35: Take a `shared_ptr<widget>&` parameter to express that a function might reseat the shared pointer](I-09-Resource%20management-R.035.md#Rr-sharedptrparam)
  * [R.36: Take a `const shared_ptr<widget>&` parameter to express that it might retain a reference count to the object ???](I-09-Resource%20management-R.036.md#Rr-sharedptrparam-const)
  * [R.37: Do not pass a pointer or reference obtained from an aliased smart pointer](I-09-Resource%20management-R.037.md#Rr-smartptrget)

