### <a name="Rconc-data"></a>CP.3: Minimize explicit sharing of writable data

##### Reason

If you don't share writable data, you can't have a data race.
The less sharing you do, the less chance you have to forget to synchronize access (and get data races).
The less sharing you do, the less chance you have to wait on a lock (so performance can improve).

##### Example

```cpp
bool validate(const vector<Reading>&);
Graph<Temp_node> temperature_gradiants(const vector<Reading>&);
Image altitude_map(const vector<Reading>&);
// ...

void process_readings(istream& socket1)
{
    vector<Reading> surface_readings;
    socket1 >> surface_readings;
    if (!socket1) throw Bad_input{};

    auto h1 = async([&] { if (!validate(surface_readings) throw Invalid_data{}; });
    auto h2 = async([&] { return temperature_gradiants(surface_readings); });
    auto h3 = async([&] { return altitude_map(surface_readings); });
    // ...
    auto v1 = h1.get();
    auto v2 = h2.get();
    auto v3 = h3.get();
    // ...
}

```
Without those `const`s, we would have to review every asynchronously invoked function for potential data races on `surface_readings`.

##### Note

Immutable data can be safely and efficiently shared.
No locking is needed: You can't have a data race on a constant.

##### Enforcement

???


