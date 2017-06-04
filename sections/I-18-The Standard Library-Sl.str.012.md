### <a name="Rstr-s"></a>Sl.str.12: Use the `s` suffix for string literals meant to be standard-library `string`s

##### Reason

Direct expression of an idea minimizes mistakes.

##### Example

    auto pp1 = make_pair("Tokyo", 9.00);         // {C-style string,double} intended?
    pair<string, double> pp2 = {"Tokyo", 9.00};  // a bit verbose
    auto pp3 = make_pair("Tokyo"s, 9.00);        // {std::string,double}    // C++17
    pair pp4 = {"Tokyo"s, 9.00};                 // {std::string,double}    // C++17


##### Note

C++17

##### Enforcement

???


## <a name="SS-io"></a>SL.io: Iostream

`iostream`s is a type safe, extensible, formatted and unformatted I/O library for streaming I/O.
It supports multiple (and user extensible) buffering strategies and multiple locales.
It can be used for conventional I/O, reading and writing to memory (string streams),
and user-defines extensions, such as streaming across networks (asio: not yet standardized).

Iostream rule summary:

* [SL.io.1: Use character-level input only when you have to](I-18-The%20Standard%20Library-SL.io.001.md#Rio-low)
* [SL.io.2: When reading, always consider ill-formed input](I-18-The%20Standard%20Library-SL.io.002.md#Rio-validate)
* [SL.io.3: Prefer iostreams for I/O](I-18-The%20Standard%20Library-SL.io.003.md#Rio-streams)
* [SL.io.10: Unless you use `printf`-family functions call `ios_base::sync_with_stdio(false)`](I-18-The%20Standard%20Library-SL.io.010.md#Rio-sync) 
* [SL.io.50: Avoid `endl`](I-18-The%20Standard%20Library-SL.io.050.md#Rio-endl)
* [???](#???)

