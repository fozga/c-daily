# Day 30 - Release polish and stress testing

## Goal
Finalize mini-grep with a stress pass, crash-hardening workflow, and release
retrospective.

## Context
Final day of the mini-grep project. Real tools must survive hostile input:
binary streams, invalid flags, huge patterns, and oversized argument lists.

## Project continuity (required)

Copy your passing Day 29 implementation into `day30/solution/` before stress testing.
This final pass validates the cumulative project built from Days 22-29.

## Task (45-60 min)
- Compile final mini-grep binary (using integrated Day 22-29 sources).
- Run `bash solution/stress_test.sh ./mini-grep`.
- If crashes occur, use ASan/GDB to locate missing validation.
- Fix remaining reliability issues.
- Fill retrospective in `solution/README.md`.

## Acceptance criteria
- `stress_test.sh` reports no crashes.
- Exit codes `0/1/2` are acceptable; `139` (segfault) and `134` (abort) are not.
- Retrospective is completed.

## Stretch goals
- Run under Valgrind while streaming `/dev/urandom` input.
