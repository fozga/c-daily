# Day 11 - Preprocessor as code generator

## Goal
Refactor macro-heavy code by fixing unsafe macro patterns and applying proper
include guards and conditional-compilation discipline.

## What you will refactor
A small utility layer where macros currently contain deliberate side-effect and
precedence bugs, plus function implementations that depend on those macros.

## Task (45-60 min)
1. Read `macros.h` and identify deliberate macro side-effect issues.
2. Fix macros to avoid double evaluation and precedence pitfalls.
3. Implement functions in `safe_ops.c` using corrected macros.
4. Run `make test`.
5. Run `make asan`.

## Acceptance criteria
- `make test` passes with zero warnings.
- `make asan` is clean.
- Macro double-evaluation bugs are fully eliminated.
- Answers to all knowledge questions are completed in `solution/README.md`.

## Knowledge check
There are 8 questions in `solution/README.md`.

## Stretch goals
Add a `STATIC_ASSERT(condition, msg)` macro that works without relying on C11
`_Static_assert`.
