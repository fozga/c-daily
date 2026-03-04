# Day 02 - Integer model and UB traps

## 1) Title + Goal

Today you will debug a numeric utility that looks simple but fails because of integer conversion rules and overflow assumptions. The goal is to build intuition for C integer behavior while keeping the strict GCC/Make workflow from Day 01.

## 2) What you will debug

You are given a small numeric library with hidden bugs related to integer promotions, signed overflow, and signed/unsigned interactions. The code compiles, but behavior is incorrect for edge cases.

## 3) Starter files

The following files are pre-created in `day02/solution/`:

- `buggy_numeric.h`
- `buggy_numeric.c`
- `tests.c`
- `Makefile`
- `README.md`

## 4) Task (45-60 min)

1. Run `make test` and observe test failures and/or warning output.
2. Identify root causes in `buggy_numeric.c`:
   - implicit conversions,
   - overflow assumptions,
   - signed/unsigned interactions.
3. Fix the implementation in `buggy_numeric.c` **without changing** the public API in `buggy_numeric.h`.
4. Add at least 6 additional tests covering boundaries, negative values, and large sizes.
5. Re-run `make asan` and `make valgrind`.
6. Write a short bug report in `solution/README.md` describing what was wrong and why.

## 5) Acceptance criteria

- `make test` passes
- 0 compiler warnings with strict flags
- `make asan` runs clean
- `make valgrind` runs clean
- `solution/README.md` contains the bug report + answers to questions

## 6) Knowledge check

Answer in `day02/solution/README.md`.

1. In `int32_t + int32_t`, what type is the expression evaluated in, and why can this still overflow?
2. How do integer promotions affect arithmetic on narrower integer types (for example `uint8_t` or `int16_t`)?
3. What are the usual arithmetic conversions, and why do mixed signed/unsigned expressions surprise people?
4. Why is signed integer overflow undefined behavior in C, but unsigned overflow defined modulo 2^N?
5. Give one practical bug pattern that appears when code assumes signed overflow wraps.
6. Why can comparing `size_t n` with `int i` produce logic bugs even when no compiler error occurs?
7. What is dangerous about subtracting two `size_t` values when the mathematical result may be negative?
8. Why do strict warnings (`-Wconversion`, `-Wsign-conversion`) matter for reliability in numeric code?
9. Given a warning like “comparison of integer expressions of different signedness,” what does it imply about the expression?
10. In a parser that returns `uint32_t`, what checks are required to reject empty strings and values outside range?

## 7) Stretch goals

- Add a reusable helper for checked addition/multiplication overflow.
- Add simple randomized tests (pseudo-random inputs with deterministic seed).
- Improve error reporting by using explicit return codes per failure mode.
