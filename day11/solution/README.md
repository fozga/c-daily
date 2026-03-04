# Day 11 Solution Workspace

## Build and run

- `make test` - build and run tests.
- `make asan` - run tests with AddressSanitizer.
- `make valgrind` - run tests under Valgrind.
- `make clean` - remove generated binaries.

## Answers

1. Why does `MAX(x++, y++)` produce unexpected results?  
   *Hint: check how many times each macro argument can be expanded/evaluated.*  
   > TODO: write your answer here.

2. Why should multi-statement macros be wrapped in `do { } while(0)`?  
   *Hint: think about `if/else` statement compatibility and single-statement behavior.*  
   > TODO: write your answer here.

3. What is the difference between `#ifdef FOO` and `#if defined(FOO)`?  
   *Hint: they are close in behavior; consider composition in larger expressions.*  
   > TODO: write your answer here.

4. When should you use `static inline` instead of a function-like macro?  
   *Hint: consider type checking, side effects, and debugging clarity.*  
   > TODO: write your answer here.

5. What happens if you define a constant with `#define` and use it in an expression with mixed types?  
   *Hint: macro replacement has no type; usual arithmetic conversions still apply later.*  
   > TODO: write your answer here.

6. Why are missing parentheses around macro parameters dangerous?  
   *Hint: operator precedence can change the intended expression meaning.*  
   > TODO: write your answer here.

7. What risks come from heavy conditional compilation (`#ifdef` sprawl)?  
   *Hint: think untested branches and maintainability.*  
   > TODO: write your answer here.

8. Why are include guards critical in C headers?  
   *Hint: repeated inclusion without guards can cause duplicate declarations/definitions.*  
   > TODO: write your answer here.
