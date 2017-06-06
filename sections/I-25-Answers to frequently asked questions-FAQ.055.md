### <a name="Faq-gsl-string-view"></a>FAQ.55: If you're using the standard types where available, why is the GSL `string_span` different from the `string_view` in the Library Fundamentals 1 Technical Specification and C++17 Working Paper? Why not just use the committee-approved `string_view`?

The consensus on the taxonomy of views for the C++ standard library was that "view" means "read-only", and "span" means "read/write". The read-only `string_view` was the first such component to complete the standardization process, while `span` and `string_span` are currently being considered for standardization.

