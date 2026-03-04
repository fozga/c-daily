# Day 18 - Singly linked list from scratch

## Goal
Implement a robust singly linked list API with clear ownership and safe edge
case handling.

## What you will build
A linked list storing integer values with proper node allocation, traversal,
lookup, removal, and cleanup semantics.

## Task (45-60 min)
- Review `slist.h`.
- Implement all `slist_` functions in `slist.c`.
- Handle edge cases: empty list, single-node list, head/tail/middle removals.
- Run `make test` until all tests pass.
- Run `make asan` and `make valgrind`.

## Acceptance criteria
- `make test` passes with 0 warnings.
- Clean ASan and Valgrind runs.
- Answers to all knowledge questions are provided.

## Knowledge check
There are 8 questions in `solution/README.md`.

## Stretch goals
Implement `slist_reverse(slist_t* list)` by relinking nodes in-place without
allocating new nodes.
