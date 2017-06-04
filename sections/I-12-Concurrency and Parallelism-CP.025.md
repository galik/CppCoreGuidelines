### <a name="Rconc-joining_thread"></a>CP.25: Prefer `gsl::joining_thread` over `std::thread`

##### Reason

A `joining_thread` is a thread that joins at the end of its scope.
Detached threads are hard to monitor.
It is harder to ensure absence of errors in detached threads (and potentially detached threads)

##### Example, bad

    void f() { std::cout << "Hello "; }

    struct F {
        void operator()() { std::cout << "parallel world "; }
    };

    int main()
    {
        std::thread t1{f};      // f() executes in separate thread
        std::thread t2{F()};    // F()() executes in separate thread
    }  // spot the bugs

##### Example

    void f() { std::cout << "Hello "; }

    struct F {
        void operator()() { std::cout << "parallel world "; }
    };

    int main()
    {
        std::thread t1{f};      // f() executes in separate thread
        std::thread t2{F()};    // F()() executes in separate thread

        t1.join();
        t2.join();
    }  // one bad bug left


##### Example, bad

The code determining whether to `join()` or `detach()` may be complicated and even decided in the thread of functions called from it or functions called by the function that creates a thread:

    void tricky(thread* t, int n)
    {
        // ...
        if (is_odd(n))
            t->detach();
        // ...
    }

    void use(int n)
    {
        thread t { tricky, this, n };
        // ...
        // ... should I join here? ...
    }

This seriously complicates lifetime analysis, and in not too unlikely cases makes lifetime analysis impossible.
This implies that we cannot safely refer to local objects in `use()` from the thread or refer to local objects in the thread from `use()`.

##### Note

Make "immortal threads" globals, put them in an enclosing scope, or put them on the on the free store rather than `detach()`.
[don't `detach`](I-12-Concurrency%20and%20Parallelism-CP.026.md#Rconc-detached_thread).

##### Note

Because of old code and third party libraries using `std::thread` this rule can be hard to introduce.

##### Enforcement

Flag uses of `std::thread`:

* Suggest use of `gsl::joining_thread`.
* Suggest ["exporting ownership"](I-12-Concurrency%20and%20Parallelism-CP.026.md#Rconc-detached_thread) to an enclosing scope if it detaches.
* Seriously warn if it is not obvious whether if joins of detaches.

