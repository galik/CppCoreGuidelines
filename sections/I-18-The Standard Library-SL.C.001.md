### <a name="Rclib-jmp"></a>SL.C.1: Don't use setjmp/longjmp

##### Reason

a `longjmp` ignores destructors, thus invalidating all resource-management strategies relying on RAII

##### Enforcement

Flag all occurrences of `longjmp`and `setjmp`



