# Day 31 - Static memory pools

## Goal
Build a fixed-size memory pool allocator using a static byte array and free-list
operations in O(1), without `malloc`/`free`.

## Context
Start of Week 5 systems patterns. In embedded and safety-critical contexts,
dynamic heap allocation is often restricted due to fragmentation and
non-deterministic timing.

## Task (45-60 min)
- Review `mempool.h`.
- Implement `pool_init` to divide a byte buffer into fixed blocks and link them.
- Implement `pool_alloc` to pop from free-list (O(1)).
- Implement `pool_free` to push back to free-list (O(1)).
- Run `make test`.

## Acceptance criteria
- `make test` passes (0 warnings).
- `pool_alloc` and `pool_free` are O(1) (no loops in those functions).
- Answers to all knowledge questions are provided.

## Knowledge check
There are 8 questions in `solution/README.md`.

## Stretch goals
- Validate in `pool_free` that pointer belongs to pool memory range.
