# Day 20 - Bitset and flag operations

## Goal
Implement a dynamic bitset for compact boolean storage using bitwise operations.

## What you will build
A memory-efficient structure over `uint64_t` blocks supporting set, clear,
toggle, and test operations across large bit domains.

## Task (45-60 min)
- Review `bitset.h`.
- Implement set/clear/test/toggle in `bitset.c`.
- Map each bit index to:
  - block index (`index / 64`)
  - bit offset (`index % 64`)
- Run `make test`.
- Run `make asan` and `make valgrind`.

## Acceptance criteria
- `make test` passes with 0 warnings.
- Clean ASan and Valgrind runs.
- Answers to all knowledge questions are provided.

## Knowledge check
There are 8 questions in `solution/README.md`.

## Stretch goals
Implement `bitset_popcount(const bitset_t* bs)` using
`__builtin_popcountll` to count all set bits.
