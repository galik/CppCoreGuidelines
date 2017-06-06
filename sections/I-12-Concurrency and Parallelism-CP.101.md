### <a name="Rconc-distrust"></a>CP.101: Distrust your hardware/compiler combination

##### Reason

The low-level hardware interfaces used by lock-free programming are among the hardest to implement well and among
the areas where the most subtle portability problems occur.
If you are doing lock-free programming for performance, you need to check for regressions.

##### Note

Instruction reordering (static and dynamic) makes it hard for us to think effectively at this level (especially if you use relaxed memory models).
Experience, (semi)formal models and model checking can be useful.
Testing - often to an extreme extent - is essential.
"Don't fly too close to the sun."

##### Enforcement

Have strong rules for re-testing in place that covers any change in hardware, operating system, compiler, and libraries.


