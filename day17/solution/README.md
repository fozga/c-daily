# Day 17 Solution Workspace

## Build and run

- `make test` - run functional tests (expected to pass despite leaks).
- `make asan` - run AddressSanitizer checks.
- `make valgrind` - run leak analysis with Memcheck.
- `make clean` - remove generated binaries.

## Answers

1. What is the difference between "definitely lost" and "still reachable"?  
   *Hint: one has no remaining pointer; the other still has at least one live reference.*  
   > TODO: write your answer here.

2. Why does an "indirectly lost" leak usually disappear when you fix the "definitely lost" leak?  
   *Hint: child allocations are often only reachable through the leaked parent object.*  
   > TODO: write your answer here.

3. What does `--track-origins=yes` do in Valgrind?  
   *Hint: think uninitialized value provenance.*  
   > TODO: write your answer here.

4. Why might a C++ developer have a harder time dealing with "still reachable" memory in C?  
   *Hint: compare RAII/destructors vs manual explicit cleanup.*  
   > TODO: write your answer here.

5. What causes the "Conditional jump depends on uninitialised value" warning?  
   *Hint: control flow decision uses bytes never initialized by program logic.*  
   > TODO: write your answer here.

6. Why should leak fixes prioritize `definitely lost` before `still reachable`?  
   *Hint: severity and ownership certainty differ.*  
   > TODO: write your answer here.

7. When is "still reachable" memory acceptable, and when should you still clean it up?  
   *Hint: process-lifetime caches vs reusable library/module shutdown.*  
   > TODO: write your answer here.

8. Why can tests pass functionally while Valgrind still reports major issues?  
   *Hint: logic correctness and memory hygiene are separate axes.*  
   > TODO: write your answer here.
