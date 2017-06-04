### <a name="Rf-conventional"></a>F.15: Prefer simple and conventional ways of passing information

##### Reason

Using "unusual and clever" techniques causes surprises, slows understanding by other programmers, and encourages bugs.
If you really feel the need for an optimization beyond the common techniques, measure to ensure that it really is an improvement, and document/comment because the improvement may not be portable.

The following tables summarize the advice in the following Guidelines, F.16-21.

Normal parameter passing:

![Normal parameter passing table](./param-passing-normal.png "Normal parameter passing")

Advanced parameter passing:

![Advanced parameter passing table](./param-passing-advanced.png "Advanced parameter passing")

Use the advanced techniques only after demonstrating need, and document that need in a comment.

