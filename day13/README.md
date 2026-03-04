# Day 13 - Module boundaries in C

## Goal
Refactor a module to enforce encapsulation with opaque types, clean translation
unit boundaries, and a disciplined public/private header split.

## What you will refactor
A key-value store module into:
- public API (`store.h`) using an opaque handle
- private internals (`store_internal.h`)
- implementation file (`store.c`) that owns the struct definition

## Task (45-60 min)
1. Review `store.h` (public API) and `store_internal.h` (private layout).
2. Implement `store.c` using internal details without exposing them publicly.
3. Ensure `tests.c` includes only `store.h` and still compiles.
4. Run `make test` until all tests pass.
5. Run `make asan` and `make valgrind`.

## Acceptance criteria
- `make test` passes with zero warnings.
- Clean ASan and Valgrind runs (no leaks).
- `tests.c` must NOT include `store_internal.h`.
- Answers to all knowledge questions are completed in `solution/README.md`.

## Knowledge check
There are 8 questions in `solution/README.md`.

## Stretch goals
Add iterator support:
`store_foreach(store_t*, void (*fn)(const char* key, int val, void* ctx), void* ctx)`.
