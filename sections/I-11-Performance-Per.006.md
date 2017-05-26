### <a name="Rper-measure"></a>Per.6: Don't make claims about performance without measurements

##### Reason

The field of performance is littered with myth and bogus folklore.
Modern hardware and optimizers defy naive assumptions; even experts are regularly surprised.

##### Note

Getting good performance measurements can be hard and require specialized tools.

##### Note

A few simple microbenchmarks using Unix `time` or the standard library `<chrono>` can help dispel the most obvious myths.
If you can't measure your complete system accurately, at least try to measure a few of your key operations and algorithms.
A profiler can help tell you which parts of your system are performance critical.
Often, you will be surprised.

???

