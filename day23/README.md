# Day 23 - Match engine v1

## Goal
Implement the mini-grep matching core for literal substring search and `.`
single-character wildcard support.

## Context
This is Day 2 of the mini-grep project. Today you build the matcher engine.
Tomorrow (Day 24) you connect it to file traversal.

## Project continuity (required)

Before coding, copy your passing Day 22 implementation into `day23/solution/`.
Keep building on that codebase from this point onward; do not restart from scratch.

## Specification

- Literal search: pattern `foo` matches any line containing substring `foo`.
- Dot wildcard: `.` in pattern matches any single character.
- `-i` mode: case-insensitive ASCII matching (without mutating original strings).

## Task (45-60 min)
- Review `matcher.h`.
- Implement `matcher_init`, `matcher_match_line`, and `matcher_destroy`.
- Run `make test`.
- Run `make asan`.

## Acceptance criteria
- `make test` passes (0 warnings).
- Clean ASan run.
- Matching behavior is correct for literals and wildcard patterns.
- Answers to all knowledge questions are provided.

## Knowledge check
There are 8 questions in `solution/README.md`.

## Stretch goals
- Add support for `^` start-anchor (pattern must match at beginning of line).
