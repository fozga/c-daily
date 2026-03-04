# Day 14 - Mini library integration day

## Goal
Assemble previous modules into a reusable static C library with a unified API
and a CLI consumer.

## What you will build
- A static library `libcdrills.a` containing implementations from three earlier
  days (recommended: days 09, 10, and 13 when available).
- A CLI tool `cdrills` with at least:
  - `parse <file>` (day09-style text parsing flow)
  - `store` (day13-style key-value interaction demo)

## Task (45-60 min)
1. Write the Makefile rules to archive objects into `libcdrills.a` using `ar`.
2. Link `libcdrills.a` into both `test_runner` and `cdrills`.
3. Implement subcommand dispatch in `cli.c`.
4. Run `make test` (integration smoke tests) and `make run`.
5. Run `make asan`.

## Acceptance criteria
- `make test` passes with zero warnings.
- `libcdrills.a` exists after build.
- `make asan` is clean.
- Answers to all knowledge questions are completed in `solution/README.md`.

## Knowledge check
There are 8 questions in `solution/README.md`.

## Stretch goals
Add a `make install` target that installs the library and umbrella header into
a local `prefix/` directory.
