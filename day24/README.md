# Day 24 - Final project: file traversal

## Goal
Process stdin and files uniformly through a scanner pipeline and print matches in
the correct output format.

## Context
Day 3 of the project. You now connect the Day 23 matcher to real input streams.
`scanner_run` handles one `FILE*`; higher-level CLI loops over file arguments.

## Specification

Output format:
- Single file or stdin: `<line_content>`
- Multiple files: `<filename>:<line_content>`
- With `-n`: add line number
  - stdin/single file: `<line_number>:<line_content>`
  - with filename: `<filename>:<line_number>:<line_content>`

## Task (45-60 min)
- Review `scanner.h`.
- Implement `scanner_run` using `fgets` (never `scanf`).
- Strip trailing newline before matching and printing.
- Integrate with `matcher_t` from Day 23 (copied into solution).
- Run `make test`.
- Run `make asan`.

## Acceptance criteria
- `make test` passes (0 warnings).
- Clean ASan and Valgrind runs.
- Output formatting matches spec exactly.
- Answers to all knowledge questions are provided.

## Knowledge check
There are 8 questions in `solution/README.md`.

## Stretch goals
- Support very long lines (>4096) with a growable buffer.
