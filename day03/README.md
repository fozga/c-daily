# Day 03 - Pointers, objects, and lifetime

## 1) Title + Goal

Today you will practice address semantics and object lifetime in C by implementing pointer-based utilities without relying on C++ references. The goal is to reason precisely about what each pointer can point to, for how long, and under what preconditions.

## 2) What you will build

A small set of safe pointer manipulation utilities in C:

- swap two integers by pointer
- reverse an integer array in place
- return a pointer to the maximum element
- copy a slice of integers with non-overlap assumptions

## 3) Task (45-60 min)

1. Review `pointers.h` to understand API contracts and return codes.
2. Implement all functions in `pointers.c`.
3. Handle `NULL` pointers defensively where required by contract.
4. Run `make test` until all assertions pass.
5. Run `make asan` and `make valgrind` to verify memory safety (no out-of-bounds reads/writes).

## 4) Acceptance criteria

- `make test` passes (0 warnings, all tests green).
- Clean ASan and Valgrind runs.
- Answers to all knowledge questions provided in `solution/README.md`.

## 5) Knowledge check

There are 8 questions in `solution/README.md` to answer.

## 6) Stretch goals

- Implement a generic memory swap (`void* a, void* b, size_t size`) without using a VLA.
