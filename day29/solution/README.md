# Day 29 Solution Workspace

## Build and run

- `make test` - build and run thread-safety tests.
- `make asan` - run tests with AddressSanitizer.
- `make valgrind` - run tests under Valgrind.
- `make clean` - remove generated binaries.

## Answers

1. Why is `count++` not thread-safe?  
   *Hint: it expands into read-modify-write steps that can interleave.*  
   > TODO: write your answer here.

2. What happens if you hold a mutex while doing file I/O?  
   *Hint: all worker threads serialize behind slow operations.*  
   > TODO: write your answer here.

3. What is the C11 equivalent of `std::mutex`?  
   *Hint: look at `<threads.h>` mutex type.*  
   > TODO: write your answer here.

4. Why might `thrd_create` fail?  
   *Hint: resource limits, OS constraints, or invalid arguments.*  
   > TODO: write your answer here.

5. If threads print to stdout at the same time, what happens to the output?  
   *Hint: writes can interleave and become non-deterministic.*  
   > TODO: write your answer here.

6. Why is the shared-index work-queue pattern useful for parallel scans?  
   *Hint: dynamic load balancing across files with uneven scan costs.*  
   > TODO: write your answer here.

7. Why should main thread join all workers before trusting final total?  
   *Hint: without join, computation may still be in progress.*  
   > TODO: write your answer here.

8. What is the tradeoff between mutex counters and atomics for this task?  
   *Hint: simplicity vs contention/performance and memory-order complexity.*  
   > TODO: write your answer here.
