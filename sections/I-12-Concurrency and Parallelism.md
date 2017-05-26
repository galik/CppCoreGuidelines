# <a name="S-concurrency"></a>CP: Concurrency and Parallelism

We often want our computers to do many tasks at the same time (or at least make them appear to do them at the same time).
The reasons for doing so varies (e.g., wanting to wait for many events using only a single processor, processing many data streams simultaneously, or utilizing many hardware facilities)
and so does the basic facilities for expressing concurrency and parallelism.
Here, we articulate a few general principles and rules for using the ISO standard C++ facilities for expressing basic concurrency and parallelism.

The core machine support for concurrent and parallel programming is the thread.
Threads allow you to run multiple instances of your program independently, while sharing
the same memory. Concurrent programming is tricky for many reasons, most
importantly that it is undefined behavior to read data in one thread after it
was written by another thread, if there is no proper synchronization between
those threads. Making existing single-threaded code execute concurrently can be
as trivial as adding `std::async` or `std::thread` strategically, or it can
necessitate a full rewrite, depending on whether the original code was written
in a thread-friendly way.

The concurrency/parallelism rules in this document are designed with three goals
in mind:

* To help you write code that is amenable to being used in a threaded
  environment
* To show clean, safe ways to use the threading primitives offered by the
  standard library
* To offer guidance on what to do when concurrency and parallelism aren't giving
  you the performance gains you need

It is also important to note that concurrency in C++ is an unfinished
story. C++11 introduced many core concurrency primitives, C++14 improved on
them, and it seems that there is much interest in making the writing of
concurrent programs in C++ even easier. We expect some of the library-related
guidance here to change significantly over time.

This section needs a lot of work (obviously).
Please note that we start with rules for relative non-experts.
Real experts must wait a bit;
contributions are welcome,
but please think about the majority of programmers who are struggling to get their concurrent programs correct and performant.

Concurrency and parallelism rule summary:

* [CP.1: Assume that your code will run as part of a multi-threaded program](I-12-Concurrency%20and%20Parallelism-CP.001.md#Rconc-multi)
* [CP.2: Avoid data races](I-12-Concurrency%20and%20Parallelism-CP.002.md#Rconc-races)
* [CP.3: Minimize explicit sharing of writable data](I-12-Concurrency%20and%20Parallelism-CP.003.md#Rconc-data)
* [CP.4: Think in terms of tasks, rather than threads](I-12-Concurrency%20and%20Parallelism-CP.004.md#Rconc-task)
* [CP.8: Don't try to use `volatile` for synchronization](I-12-Concurrency%20and%20Parallelism-CP.008.md#Rconc-volatile)
* [CP.9: Whenever feasible use tools to validate your concurrent code](I-12-Concurrency%20and%20Parallelism-CP.009.md#Rconc-tools)

See also:

* [CP.con: Concurrency](I-12-Concurrency%20and%20Parallelism-CP.009.md#SScp-con)
* [CP.par: Parallelism](I-12-Concurrency%20and%20Parallelism-P.050.md#SScp-par)
* [CP.mess: Message passing](I-12-Concurrency%20and%20Parallelism-P.050.md#SScp-mess)
* [CP.vec: Vectorization](I-12-Concurrency%20and%20Parallelism-CP.061.md#SScp-vec)
* [CP.free: Lock-free programming](I-12-Concurrency%20and%20Parallelism-CP.061.md#SScp-free)
* [CP.etc: Etc. concurrency rules](I-12-Concurrency%20and%20Parallelism-CP.111.md#SScp-etc)

