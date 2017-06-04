### <a name="Ri-typed"></a>I.4: Make interfaces precisely and strongly typed

##### Reason

Types are the simplest and best documentation, have well-defined meaning, and are guaranteed to be checked at compile time.
Also, precisely typed code is often optimized better.

##### Example, don't

Consider:

    void pass(void* data);    // void* is suspicious

Now the callee must cast the data pointer (back) to a correct type to use it. That is error-prone and often verbose.
Avoid `void*`, especially in interfaces.
Consider using a `variant` or a pointer to base instead.

**Alternative**: Often, a template parameter can eliminate the `void*` turning it into a `T*` or `T&`.
For generic code these `T`s can be general or concept constrained template parameters.

##### Example, bad

Consider:

    void draw_rect(int, int, int, int);   // great opportunities for mistakes

    draw_rect(p.x, p.y, 10, 20);          // what does 10, 20 mean?

An `int` can carry arbitrary forms of information, so we must guess about the meaning of the four `int`s.
Most likely, the first two are an `x`,`y` coordinate pair, but what are the last two?
Comments and parameter names can help, but we could be explicit:

    void draw_rectangle(Point top_left, Point bottom_right);
    void draw_rectangle(Point top_left, Size height_width);

    draw_rectangle(p, Point{10, 20});  // two corners
    draw_rectangle(p, Size{10, 20});   // one corner and a (height, width) pair

Obviously, we cannot catch all errors through the static type system
(e.g., the fact that a first argument is supposed to be a top-left point is left to convention (naming and comments)).

##### Example, bad

In the following example, it is not clear from the interface what `time_to_blink` means: Seconds? Milliseconds?

    void blink_led(int time_to_blink) // bad -- the unit is ambiguous
    {
        // ...
        // do something with time_to_blink
        // ...
    }

    void use()
    {
        blink_led(2);
    }

##### Example, good

`std::chrono::duration` types (C++11) helps making the unit of time duration explicit.

    void blink_led(milliseconds time_to_blink) // good -- the unit is explicit
    {
        // ...
        // do something with time_to_blink
        // ...
    }

    void use()
    {
        blink_led(1500ms);
    }

The function can also be written in such a way that it will accept any time duration unit.

    template<class rep, class period>
    void blink_led(duration<rep, period> time_to_blink) // good -- accepts any unit
    {
        // assuming that millisecond is the smallest relevant unit
        auto milliseconds_to_blink = duration_cast<milliseconds>(time_to_blink);
        // ...
        // do something with milliseconds_to_blink
        // ...
    }

    void use()
    {
        blink_led(2s);
        blink_led(1500ms);
    }

##### Enforcement

* (Simple) Report the use of `void*` as a parameter or return type.
* (Hard to do well) Look for member functions with many built-in type arguments.

