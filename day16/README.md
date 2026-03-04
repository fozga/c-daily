# Day 16 - Catch memory bugs with ASan

## Goal
Use AddressSanitizer (ASan) to detect hidden memory safety defects and fix them.

## What you will debug
A module that may appear to work in plain test runs but contains severe memory
violations that ASan reports precisely.

## Task (45-60 min)
- Run `make test` and observe behavior (may pass or fail unpredictably).
- Run `make asan` and inspect ASan reports.
- Read report sections like `READ/WRITE of size`, `freed by`, `allocated by`.
- Fix the three distinct bugs in `faulty_heap.c`.
- Re-run `make asan` until the run is clean.

## Acceptance criteria
- Clean `make asan` run (no ASan reports).
- `solution/README.md` contains a short description of the three bugs found.
- Answers to all knowledge questions are provided.

## Knowledge check
There are 8 questions in `solution/README.md`.

## Stretch goals
Create a small extra function that triggers a stack-buffer-overflow and inspect
its ASan report to practice interpretation.
