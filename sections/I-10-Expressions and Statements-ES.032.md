### <a name="Res-ALL_CAPS"></a>ES.32: Use `ALL_CAPS` for all macro names

##### Reason

Convention. Readability. Distinguishing macros.

##### Example

    #define forever for (;;)   /* very BAD */

    #define FOREVER for (;;)   /* Still evil, but at least visible to humans */

##### Enforcement

Scream when you see a lower case macro.

