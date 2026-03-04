# Day 09 - Robust text input parsing

## Goal
Build a robust text parser using `fgets`, `strtol`, `sscanf`, and explicit
validation to safely read CSV-like records.

## What you will build
A line parser that reads records in the form `id,name,score` from a `FILE*`
source and reports precise error codes for malformed input.

## Task (45-60 min)
1. Review `line_parser.h` to understand the API and error codes.
2. Implement `lp_read_line` and `lp_parse_record` in `line_parser.c`.
3. Never parse directly from `stdin` with `scanf`; read full lines with `fgets`.
4. Set `errno` correctly when numeric parsing fails.
5. Run `make test` until all tests pass.
6. Run `make asan`.

## Acceptance criteria
- `make test` passes with zero warnings.
- `make asan` is clean.
- Malformed input lines return specific error codes (no crashes).
- Answers to all knowledge questions are completed in `solution/README.md`.

## Knowledge check
There are 8 questions in `solution/README.md`.

## Stretch goals
- Support optional trailing whitespace.
- Support comment lines beginning with `#`.
