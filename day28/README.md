# Day 28 - Project series I: regex-lite sets

## Goal
Extend matcher syntax with bracket character classes and escapes while preserving
existing Day 23 behavior.

## Context
Day 7 of the project and Part 1 of the 3-part series (Days 28-30). You evolve
the pattern language without breaking prior functionality.

## New syntax

- `[abc]` matches one char from set `{a,b,c}`
- `[a-z]` matches ASCII range
- `[^abc]` negated class
- escapes: `\n`, `\t`, `\\`

## Task (45-60 min)
- Review `matcher2.h`.
- Implement matcher logic for literals, `.`, classes, negation, and escapes.
- Ensure `-i` case-insensitive mode applies to range/class comparisons too.
- Run `make test`.
- Run `make asan`.

## Acceptance criteria
- `make test` passes (0 warnings).
- Clean ASan run.
- All Day 23 behavior still passes unchanged.
- Answers to all knowledge questions are provided.

## Knowledge check
There are 8 questions in `solution/README.md`.

## Stretch goals
- Support negated ranges such as `[^a-z]`.
