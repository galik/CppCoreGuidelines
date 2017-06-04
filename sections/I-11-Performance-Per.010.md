### <a name="Rper-type"></a>Per.10: Rely on the static type system

##### Reason

Type violations, weak types (e.g. `void*`s), and low level code (e.g., manipulation of sequences as individual bytes) make the job of the optimizer much harder. Simple code often optimizes better than hand-crafted complex code.

???

