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

**Q1: The expression `(unsigned int)(-1) < 2u` evaluates to false. Trace through the conversion rules that produce this result and name the specific standard mechanism.**  

> Your answer here...

---

**Q2: Why is signed integer overflow undefined behavior in C, while unsigned overflow is guaranteed to wrap modulo 2^N? What assumption does this let the optimizer make about signed arithmetic that it cannot make about unsigned arithmetic?**  

> Your answer here...

---

**Q3: The loop `for (size_t i = n - 1; i >= 0; --i)` is intended to count down from `n-1` to `0`. Identify the bug, explain why the comparison can never be false, and rewrite the loop correctly.**  

> Your answer here...

---

**Q4: Write a safe pre-addition overflow check for two `int32_t` values that does not itself invoke undefined behavior. Explain why checking `a + b < a` after the addition is incorrect.**  

> Your answer here...

---

**Q5: `uint8_t` arithmetic operands do not stay 8-bit during computation. What type do they promote to, and what consequence does this have if the result is stored back into a `uint8_t` without an explicit cast?**  

> Your answer here...

---

**Q6: A function parses user input via `strtoul` into `uint32_t`. Name three distinct checks required before using the result as an array index into a buffer of known capacity `cap`.**  

> Your answer here...

---

**Q7: Beyond `-Wall -Wextra`, name two warning flags most effective at catching signed/unsigned conversion bugs. Give one example diagnostic message each would produce.**  

> Your answer here...

---

**Q8: When should a loop counter be typed as `size_t` rather than `int32_t`? State the deciding criterion and identify one hazard that `size_t` introduces for descending loops.**  

> Your answer here...
