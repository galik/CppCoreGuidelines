### <a name="Rconc-create"></a>CP.41: Minimize thread creation and destruction

##### Reason

Thread creation is expensive.

##### Example

```cpp
void worker(Message m)
{
    // process
}

void master(istream& is)
{
    for (Message m; is >> m; )
        run_list.push_back(new thread(worker, m));
}

```
This spawns a `thread` per message, and the `run_list` is presumably managed to destroy those tasks once they are finished.

Instead, we could have a set of pre-created worker threads processing the messages

```cpp
Sync_queue<Message> work;

void master(istream& is)
{
    for (Message m; is >> m; )
        work.put(m);
}

void worker()
{
    for (Message m; m = work.get(); ) {
        // process
    }
}

void workers()  // set up worker threads (specifically 4 worker threads)
{
    joining_thread w1 {worker};
    joining_thread w2 {worker};
    joining_thread w3 {worker};
    joining_thread w4 {worker};
}

```
##### Note

If your system has a good thread pool, use it.
If your system has a good message queue, use it.

##### Enforcement

???


