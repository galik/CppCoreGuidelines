### <a name="Ri-abi"></a>I.26: If you want a cross-compiler ABI, use a C-style subset

##### Reason

Different compilers implement different binary layouts for classes, exception handling, function names, and other implementation details.

##### Exception

You can carefully craft an interface using a few carefully selected higher-level C++ types. See ???.

##### Exception

Common ABIs are emerging on some platforms freeing you from the more draconian restrictions.

##### Note

If you use a single compiler, you can use full C++ in interfaces. That may require recompilation after an upgrade to a new compiler version.

##### Enforcement

(Not enforceable) It is difficult to reliably identify where an interface forms part of an ABI.

