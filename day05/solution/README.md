# Day 05 Solution Workspace

Implement the `strview` API in `strview.c` using only pointer+length logic. Do not rely on NUL-termination in algorithm loops.

## Build and test

```bash
make test
make asan
make valgrind
make clean
```

## Answers

**Q1: A loop recomputes `strlen(s)` on every iteration: `for (size_t i = 0; i < strlen(s); ++i)`. Describe the algorithmic cost in big-O terms and explain why the optimizer usually cannot eliminate the repeated scan.**  

> Your answer here...

---

**Q2: What happens if you pass a string without a `\0` to a standard C function expecting a C-string?**  

> Your answer here...

---

**Q3: Why is a String View struct typically faster for taking substrings than a standard C-string approach?**  

> Your answer here...

---

**Q4: You are implementing `strview_split(strview s, char delim, strview* left, strview* right)` that divides `s` at the first occurrence of `delim`. Sketch the pointer arithmetic to compute both sub-views, and name one boundary case (besides delim-not-found) that must be explicitly handled to avoid undefined behavior.**  

> Your answer here...

---

**Q5: Why is `printf("%s", view.data)` dangerous for generic `strview` data?**  

> Your answer here...

---

**Q6: Conceptually, why is view equality closer to `memcmp` than `strcmp`?**  

> Your answer here...

---

**Q7: In a C API, why must pointer lifetime and view length both be part of the contract?**  

> Your answer here...

---

**Q8: `strncpy(dst, src, sizeof(dst))` is supposed to be a safe copy. Describe two situations where this code still produces a bug, and write the minimal correction for each.**  

> Your answer here...
