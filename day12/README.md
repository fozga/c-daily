# Day 12 - Struct design and memory layout

## Goal
Debug and fix a binary compatibility bug caused by implicit struct padding and
alignment assumptions.

## What you will debug
A binary read/write routine that appears to work locally but relies on a struct
layout that is not deterministic across builds and platforms.

## Task (45-60 min)
1. Compile with `-Wpadded` and inspect layout warnings.
2. Use `sizeof` and `offsetof` to inspect real struct layout.
3. Fix layout by reordering fields and using fixed-width types.
4. Run `make test` until round-trip behavior passes.
5. Run `make asan`.

## Acceptance criteria
- `make test` passes with zero warnings (without adding `-Wpadded` to default flags).
- Round-trip binary write/read produces identical data.
- Answers to all knowledge questions are completed in `solution/README.md`.

## Knowledge check
There are 8 questions in `solution/README.md`.

## Stretch goals
Use `_Static_assert` to enforce expected struct size at compile time.
