# Day 06 - Heap ownership in C

## 1) Title + Goal

Today you will practice explicit heap lifecycles in C using `malloc`/`realloc`/`free`. The goal is to implement an API with clear ownership rules and safe create/destroy behavior.

## 2) What you will build

You will implement a dynamic string buffer (`dyn_string`) that owns heap memory and grows automatically as new data is appended.

## 3) Task (45-60 min)

1. Review `dyn_string.h` to understand ownership semantics (who is responsible for calling `free`).
2. Implement the functions in `dyn_string.c` using `malloc`, `realloc`, and `free` from `<stdlib.h>`.
3. Ensure allocation failures are handled gracefully (for example, if `malloc` returns `NULL`).
4. Run `make test` to verify your logic.
5. Run `make asan` and `make valgrind`. Valgrind is the most important tool today and should report `0 bytes definitely lost`.

## 4) Acceptance criteria

- `make test` passes (0 warnings).
- Clean ASan run (no buffer overflows).
- Clean Valgrind run (no memory leaks, no double frees).
- Answers to all knowledge questions provided in `solution/README.md`.

## 5) Knowledge check

There are 8 questions in `solution/README.md` to answer.

## 6) Stretch goals

- Implement exponential growth (for example, doubling capacity) instead of linear growth when `realloc` is needed.
- Add a `dyn_string_steal` function that returns the underlying `char*`, transferring the obligation to call `free` to the caller.
