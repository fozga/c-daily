# Day 02 Solution Workspace

This workspace starts with intentionally buggy numeric code. Your job is to debug it using strict warnings and edge-case tests.

## What to do

1. Run `make test` and inspect failing test messages.
2. Read `buggy_numeric.h` to understand expected behavior.
3. Fix bugs in `buggy_numeric.c` without changing the public API.
4. Add at least 6 extra tests to `tests.c`.
5. Run `make asan` and `make valgrind` after fixes.
6. Fill in the bug report and answers below.

## How to run

```bash
make test
make asan
make valgrind
make clean
```

## Bug report

### Symptoms

> Describe what failed first (tests, suspicious values, warnings).

### Root cause

> Explain the conversion/overflow/signedness mistakes that caused the failures.

### Fix

> Summarize exactly what you changed in `buggy_numeric.c`.

### Tests added

> List at least 6 additional tests and what edge cases they cover.

### What I learned

> Write 3-5 bullets on integer promotions, UB, and safer numeric patterns.

## Answers

**Q1: In `int32_t + int32_t`, what type is the expression evaluated in, and why can this still overflow?**  
*Hint: see `../materials/notes.md` -> Section 2*

> Your answer here...

---

**Q2: How do integer promotions affect arithmetic on narrower integer types (for example `uint8_t` or `int16_t`)?**  
*Hint: see `../materials/notes.md` -> Section 2*

> Your answer here...

---

**Q3: What are the usual arithmetic conversions, and why do mixed signed/unsigned expressions surprise people?**  
*Hint: see `../materials/notes.md` -> Section 2*

> Your answer here...

---

**Q4: Why is signed integer overflow undefined behavior in C, but unsigned overflow defined modulo 2^N?**  
*Hint: see `../materials/notes.md` -> Section 3*

> Your answer here...

---

**Q5: Give one practical bug pattern that appears when code assumes signed overflow wraps.**  
*Hint: see `../materials/notes.md` -> Section 3*

> Your answer here...

---

**Q6: Why can comparing `size_t n` with `int i` produce logic bugs even when no compiler error occurs?**  
*Hint: see `../materials/notes.md` -> Section 4*

> Your answer here...

---

**Q7: What is dangerous about subtracting two `size_t` values when the mathematical result may be negative?**  
*Hint: see `../materials/notes.md` -> Section 4*

> Your answer here...

---

**Q8: Why do strict warnings (`-Wconversion`, `-Wsign-conversion`) matter for reliability in numeric code?**  
*Hint: see `../materials/notes.md` -> Section 6*

> Your answer here...

---

**Q9: Given a warning like “comparison of integer expressions of different signedness,” what does it imply about the expression?**  
*Hint: see `../materials/notes.md` -> Section 6*

> Your answer here...

---

**Q10: In a parser that returns `uint32_t`, what checks are required to reject empty strings and values outside range?**  
*Hint: see `../materials/notes.md` -> Sections 5 and 7*

> Your answer here...
