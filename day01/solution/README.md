# Day 01 Solution Workspace

Purpose: implement a small multi-file C11 exercise and practice the full GCC + Make workflow (compile, test, sanitize, and memory-check).

Create these files in this directory:

- `main.c`
- `util.c`
- `util.h`
- `tests.c`

Suggested implementation flow:

1. Implement a string reversal function in `util.c`.
2. Expose its declaration in `util.h` with proper include guards.
3. Call it from `main.c` for a manual run.
4. Write at least 3 assertions in `tests.c`.

## How to run

```bash
make test
make asan
make valgrind
make clean
```

## Answers

**Q1: Your project has `main.c`, `util.c`, and `util.h`. You run `gcc main.c -o app` and get `undefined reference to util_reverse_string`. Explain precisely why the linker fails, and write the minimal corrected command.**  

> Your answer here...

---

**Q2: A header `config.h` is included by both `main.c` and `util.c`. Without include guards, what specific error occurs during compilation, and exactly which pipeline stage produces it?**  

> Your answer here...

---

**Q3: What content belongs in `util.h` and what must stay in `util.c`? Give one concrete example of content that, if placed in the header, causes a multiple-definition link error when `main.c` and `tests.c` both include it.**  

> Your answer here...

---

**Q4: `-Wall` is enabled, but the compiler does not warn about a variable shadowed in an inner block. Name the additional flag that catches this, and explain why the compiler considers shadowing a noteworthy hazard.**  

> Your answer here...

---

**Q5: A colleague builds with `-O2 -g` and insists the debug info is "just as useful" as `-O0 -g`. Describe two specific ways that `-O2` makes source-level debugging unreliable, and name the optimizations responsible.**  

> Your answer here...

---

**Q6: In Make, a file named `test` is accidentally created in the build directory. Without `.PHONY: test`, what does `make test` do now, and how does declaring it `.PHONY` fix this?**  

> Your answer here...

---

**Q7: You run your test suite under ASan and find a heap-buffer-overflow. You then want to check for leaks with Valgrind. Why can you not simply run Valgrind on the same ASan-instrumented binary, and what is the correct workflow?**  

> Your answer here...

---

**Q8: GDB reports a crash inside `util_reverse_string` but the source line shown is incorrect. What build-time mistake caused this mismatch, and what must you do before relaunching GDB?**  

> Your answer here...
