### <a name="Rnr-lots-of-files"></a>NR.4: Don't: Place each class declaration in its own source file

##### Reason (not to follow this rule)

The resulting number of files are hard to manage and can slow down compilation.
Individual classes are rarely a good logical unit of maintenance and distribution.

##### Example

    ???

##### Alternative

* Use namespaces containing logically cohesive sets of classes and functions.

