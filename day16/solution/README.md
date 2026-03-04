# Day 16 Solution Workspace

## Build and run

- `make test` - run baseline tests (may pass despite hidden memory bugs).
- `make asan` - run AddressSanitizer build and inspect bug reports.
- `make valgrind` - optional secondary runtime memory checks.
- `make clean` - remove generated binaries.

## Bugs Found

Document the three bugs you identify and fix:

1. `TODO`
2. `TODO`
3. `TODO`

## Answers

1. What is "shadow memory" in the context of ASan?  
   *Hint: ASan keeps metadata for real memory regions.*  
   > TODO: write your answer here.

2. What is a "redzone"?  
   *Hint: think poisoned guard bytes around objects.*  
   > TODO: write your answer here.

3. Why does ASan need to override the `malloc` and `free` functions?  
   *Hint: allocation lifetime tracking is required for use-after-free detection.*  
   > TODO: write your answer here.

4. What does heap-use-after-free mean?  
   *Hint: object lifetime ended but pointer is still used.*  
   > TODO: write your answer here.

5. Name one thing ASan can catch that Valgrind Memcheck cannot.  
   *Hint: stack/global boundary instrumentation is a clue.*  
   > TODO: write your answer here.

6. Why is `-fno-omit-frame-pointer` useful with ASan?  
   *Hint: call stacks become easier to resolve.*  
   > TODO: write your answer here.

7. What does "WRITE of size 1" in an ASan report tell you?  
   *Hint: it describes the access type and byte width at fault.*  
   > TODO: write your answer here.

8. Why might a non-ASan test run appear fine even when memory bugs exist?  
   *Hint: undefined behavior can stay latent without instrumentation.*  
   > TODO: write your answer here.
