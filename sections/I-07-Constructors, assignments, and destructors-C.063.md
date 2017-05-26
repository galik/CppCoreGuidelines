### <a name="Rc-move-assignment"></a>C.63: Make move assignment non-`virtual`, take the parameter by `&&`, and return by non-`const &`

##### Reason

It is simple and efficient.

**See**: [The rule for copy-assignment](I-07-Constructors, assignments, and destructors-C.060.md#Rc-copy-assignment).

##### Enforcement

Equivalent to what is done for [copy-assignment](I-07-Constructors, assignments, and destructors-C.060.md#Rc-copy-assignment).

* (Simple) An assignment operator should not be virtual. Here be dragons!
* (Simple) An assignment operator should return `T&` to enable chaining, not alternatives like `const T&` which interfere with composability and putting objects in containers.
* (Moderate) A move assignment operator should (implicitly or explicitly) invoke all base and member move assignment operators.

