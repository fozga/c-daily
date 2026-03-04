# Day 21 - Defensive and testable C

## Goal
Refactor C code with defensive checks, invariants, and fault-injection seams.

## What you will refactor
A simple singly linked list implementation that works in normal paths but lacks
internal verification and allocator failure testability.

## Task (45-60 min)
- Review `slist_defensive.c` baseline logic.
- Replace raw `malloc` calls with `MALLOC_SEAM(size)`.
- Use `test_set_malloc_fail_at` to simulate allocation failures in tests.
- Implement `slist_verify_invariants(const slist_t* list)`.
- Call `slist_verify_invariants` after every mutating function.
- Run `make test`.

## Acceptance criteria
- `make test` passes.
- Fault injection tests prove clean behavior on OOM paths.
- Invariant checks can detect internal corruption.
- Answers to all knowledge questions are provided.

## Knowledge check
There are 8 questions in `solution/README.md`.

## Stretch goals
Implement `ASSERT_MSG(cond, msg)` that reports file/line and aborts cleanly.
