# Day 21 Solution Workspace

## Build and run

- `make test` - build and run tests.
- `make asan` - run tests with AddressSanitizer.
- `make valgrind` - run tests with Valgrind.
- `make clean` - remove generated binaries.

## Answers

1. What happens if you put code with side-effects inside an `assert()`?  
   *Hint: assertions can be compiled out with `NDEBUG`.*  
   > TODO: write your answer here.

2. How do you turn off assertions in a production build using GCC?  
   *Hint: define the macro that disables assert checks.*  
   > TODO: write your answer here.

3. Why should out-of-memory handling be tested using a "seam" rather than real OOM?  
   *Hint: deterministic and reproducible failure injection.*  
   > TODO: write your answer here.

4. What is a data structure "invariant"?  
   *Hint: condition that must remain true for valid state.*  
   > TODO: write your answer here.

5. If user input is invalid, should you use assert or return an error code?  
   *Hint: user/runtime errors are expected paths, not developer bugs.*  
   > TODO: write your answer here.

6. Why run invariant checks after mutating operations?  
   *Hint: catch corruption at the point it is introduced.*  
   > TODO: write your answer here.

7. What is the benefit of a `MALLOC_SEAM` macro in C modules?  
   *Hint: swappable allocation behavior for tests.*  
   > TODO: write your answer here.

8. Why should test code reset fault injection state between tests?  
   *Hint: avoid order-dependent flaky failures.*  
   > TODO: write your answer here.
