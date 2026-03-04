# Day 11 Solution Workspace

## Build and run

- `make test` - build and run tests.
- `make asan` - run tests with AddressSanitizer.
- `make valgrind` - run tests under Valgrind.
- `make clean` - remove generated binaries.

## Answers

**Q1: `MAX(i++, j++)` where `i = 3, j = 5`. Trace the expansion step by step and show the final values of `i` and `j`. What does this reveal about how the preprocessor handles arguments?**  

> Your answer here...

---

**Q2: Show a concrete `if/else` fragment that breaks silently when a two-statement macro is NOT wrapped in `do { } while (0)`. Then show how the wrapper fixes it.**  

> Your answer here...

---

**Q3: `#ifdef FOO` and `#if defined(FOO)` both test whether `FOO` is defined. Describe a situation where only `#if defined(FOO)` works and `#ifdef FOO` cannot be used.**  

> Your answer here...

---

**Q4: You have a function-like macro `CLAMP(val, lo, hi)` that appears in a hot loop. Give two reasons to prefer a `static inline` function, and one legitimate reason to keep it as a macro.**  

> Your answer here...

---

**Q5: `#define TIMEOUT 30` is used in `sleep(TIMEOUT / 1000.0)`. What type does `TIMEOUT` have at the point of expansion, and what result does the division produce? How would you fix it?**  

> Your answer here...

---

**Q6: `#define ADD(a, b) a + b` is used as `int x = ADD(2, 3) * 4`. What is the result and why? Rewrite the macro to produce the mathematically expected answer.**  

> Your answer here...

---

**Q7: A codebase has 15 nested `#ifdef` blocks controlling platform differences. Describe two concrete maintenance problems this creates and suggest a better architectural approach.**  

> Your answer here...

---

**Q8: A header is included from three `.c` files. Without include guards, what exact compiler error can occur and why? Would `#pragma once` solve the same problem?**  

> Your answer here...

---
