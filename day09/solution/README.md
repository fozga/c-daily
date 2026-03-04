# Day 09 Solution Workspace

## Build and run

- `make test` - build and run tests.
- `make asan` - run tests with AddressSanitizer.
- `make valgrind` - run tests under Valgrind.
- `make clean` - remove generated binaries.

## Answers

**Q1: Why does `scanf("%s", buf)` without a width specifier constitute a buffer overflow vulnerability, even when used in a controlled environment?**  

> Your answer here...

---

**Q2: Walk through every check the safe `strtol` pattern requires in order. What bug does each check catch that the previous checks do not?**  

> Your answer here...

---

**Q3: A parser calls `strtol` and the return value is `LONG_MAX` with `errno == ERANGE`. The input string was `"99999999999999999999"`. What exactly went wrong, and how do you surface this as a distinct error code to the caller?**  

> Your answer here...

---

**Q4: `fgets` was called with `buf[64]` and a 63-character line followed by `\n`. Describe exactly what `buf` contains afterward. How does the answer change if the line is 64 characters with no `\n`?**  

> Your answer here...

---

**Q5: After `fgets` returns NULL, how do you distinguish a normal end-of-file from an actual I/O error, and why does that distinction matter for error reporting?**  

> Your answer here...

---

**Q6: Your parser accepts `"42abc"` as the valid integer `42` because `strtol` stops at `'a'`. Which step of the safe conversion sequence catches this, and what should be returned to the caller?**  

> Your answer here...

---

**Q7: Explain why returning a single generic `PARSE_ERROR` for all malformed cases is bad design. Give two examples of failure modes that a caller would need to distinguish.**  

> Your answer here...

---

**Q8: Compare using `sscanf` directly versus the `fgets`-then-tokenize-then-`strtol` approach for parsing `"id,name,score"` records. When would `sscanf` be acceptable and when does it fail you?**  

> Your answer here...

---
