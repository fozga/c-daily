# Day 20 Solution Workspace

## Build and run

- `make test` - build and run tests.
- `make asan` - run tests with AddressSanitizer.
- `make valgrind` - run tests with Valgrind.
- `make clean` - remove generated binaries.

## Answers

1. What is the difference between `&` and `&&` in C?  
   *Hint: one is bitwise, the other is logical with short-circuit behavior.*  
   > TODO: write your answer here.

2. Why should you always use unsigned types like `uint64_t` for bit manipulation?  
   *Hint: signed shifts/overflow semantics can be implementation-defined or undefined.*  
   > TODO: write your answer here.

3. Why is `1 << 40` a bug, and how do you fix it?  
   *Hint: integer literal type width matters; use a 64-bit unsigned literal.*  
   > TODO: write your answer here.

4. What bitwise operation sets a specific bit to `1` without changing others?  
   *Hint: use OR with a single-bit mask.*  
   > TODO: write your answer here.

5. What bitwise operation clears a specific bit to `0` without changing others?  
   *Hint: combine AND with inverted mask.*  
   > TODO: write your answer here.

6. How do you compute block index and bit offset in a `uint64_t` bitset?  
   *Hint: division and modulo by 64.*  
   > TODO: write your answer here.

7. What operation toggles a bit?  
   *Hint: XOR flips bit value when mask bit is 1.*  
   > TODO: write your answer here.

8. Why are bounds checks essential in dynamic bitset APIs?  
   *Hint: out-of-range indexes can corrupt unrelated memory.*  
   > TODO: write your answer here.
