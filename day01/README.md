# Day 01 - GCC and Make workflow

## Title & Goal

Set up a clean GCC + Make workflow for C on Linux and understand compilation units, linking, and practical Make targets.

## What you will build

A small multi-file C11 program in `solution/` with:

- `main.c`
- `util.c`
- `util.h`
- `tests.c`

Use strict debug-oriented flags during compilation:

- `-std=c11 -O0 -g -Wall -Wextra -Wpedantic -Werror`

## Task (45-60 min)

1. Write a simple string-reversal utility in `util.c` with its declaration in `util.h`.
2. Write a `main.c` that uses it.
3. Write a `tests.c` with at least 3 basic assertions.

## Acceptance criteria

- Code compiles with zero warnings.
- Tests pass via `make test`.
- `make asan` runs cleanly (no AddressSanitizer errors).
- `make valgrind` runs cleanly (no leaks or invalid memory access).

## Suggested Make usage

From `day01/solution/`:

- `make test` - compile and run test binary.
- `make asan` - compile with AddressSanitizer and run tests.
- `make valgrind` - run tests under Valgrind Memcheck.
- `make clean` - remove binaries and object files.

## Knowledge check questions

1. What are the 4 stages of the GCC compilation pipeline?
2. You compiled `main.c` successfully, but linker reports `undefined reference to util_reverse_string`. What is the most likely cause?
3. What command runs only preprocessing for `main.c` so you can inspect expanded includes/macros?
4. What should go into `util.h`, and what should usually stay out of headers?
5. Why do include guards prevent multiple definition/redefinition problems?
6. How is `#include <stdio.h>` different from `#include "util.h"` in header search behavior?
7. What is the practical difference between `-Wall` and `-Wextra`, and why is `-Wall` not enough alone?
8. Which flag turns warnings into build failures, and why is that useful in daily practice?
9. You suspect a variable is accidentally shadowed in an inner scope. Which warning flag should you add?
10. What information does `-g` add to a binary, and how does GDB use it?
11. Why is `-O0 -g` preferred for debugging over `-O2 -g`?
12. In a Make rule, what do `$@`, `$^`, and `$<` expand to?
13. Why should targets like `test` and `clean` be listed under `.PHONY`?
14. What kinds of memory bugs does AddressSanitizer catch, and what flag must be present at both compile and link time?
15. Why should Valgrind Memcheck be run on a non-ASan debug build, and which leak category is the strongest fix-now signal?

