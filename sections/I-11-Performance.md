# <a name="S-performance"></a>Per: Performance

??? should this section be in the main guide???

This section contains rules for people who need high performance or low-latency.
That is, these are rules that relate to how to use as little time and as few resources as possible to achieve a task in a predictably short time.
The rules in this section are more restrictive and intrusive than what is needed for many (most) applications.
Do not blindly try to follow them in general code: achieving the goals of low latency requires extra work.

Performance rule summary:

* [Per.1: Don't optimize without reason](I-11-Performance-Per.001.md#Rper-reason)
* [Per.2: Don't optimize prematurely](I-11-Performance-Per.002.md#Rper-Knuth)
* [Per.3: Don't optimize something that's not performance critical](I-11-Performance-Per.003.md#Rper-critical)
* [Per.4: Don't assume that complicated code is necessarily faster than simple code](I-11-Performance-Per.004.md#Rper-simple)
* [Per.5: Don't assume that low-level code is necessarily faster than high-level code](I-11-Performance-Per.005.md#Rper-low)
* [Per.6: Don't make claims about performance without measurements](I-11-Performance-Per.006.md#Rper-measure)
* [Per.7: Design to enable optimization](I-11-Performance-Per.007.md#Rper-efficiency)
* [Per.10: Rely on the static type system](I-11-Performance-Per.010.md#Rper-type)
* [Per.11: Move computation from run time to compile time](I-11-Performance-Per.011.md#Rper-Comp)
* [Per.12: Eliminate redundant aliases](I-11-Performance-Per.012.md#Rper-alias)
* [Per.13: Eliminate redundant indirections](I-11-Performance-Per.013.md#Rper-indirect)
* [Per.14: Minimize the number of allocations and deallocations](I-11-Performance-Per.014.md#Rper-alloc)
* [Per.15: Do not allocate on a critical branch](I-11-Performance-Per.015.md#Rper-alloc0)
* [Per.16: Use compact data structures](I-11-Performance-Per.016.md#Rper-compact)
* [Per.17: Declare the most used member of a time-critical struct first](I-11-Performance-Per.017.md#Rper-struct)
* [Per.18: Space is time](I-11-Performance-Per.018.md#Rper-space)
* [Per.19: Access memory predictably](I-11-Performance-Per.019.md#Rper-access)
* [Per.30: Avoid context switches on the critical path](I-11-Performance-Per.030.md#Rper-context)

