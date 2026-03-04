# Day 25 - Final project: diagnostics hardening

## Goal
Add robust diagnostics and exit-status mapping so mini-grep reports failures
clearly without crashing and follows Unix-like behavior.

## Context
Day 4 of the project. You now add an error-reporting layer:
- print actionable errors to stderr
- continue processing remaining files
- return correct final exit code based on outcomes

## Specification

- On `fopen` failure: print  
  `mini-grep: <filename>: <strerror(errno)>` to stderr.
- Partial success (some files failed): exit with `1`.
- No matches and no errors: exit with `1` (grep convention).
- Only errors and no successful matches: exit with `2`.

## Task (45-60 min)
- Implement `diag_open_file` in `diag.c`.
- Implement summary exit-code logic.
- Run `make test`.
- Run `make asan`.

## Acceptance criteria
- `make test` passes (0 warnings).
- Clean ASan run.
- Exit-code mapping is correct in all required scenarios.
- Answers to all knowledge questions are provided.

## Knowledge check
There are 8 questions in `solution/README.md`.

## Stretch goals
- Add `--silent` / `-s` flag to suppress printed diagnostics.
