# Day 22 - mini-grep CLI skeleton

## Goal
Build the CLI foundation for mini-grep: argument parsing, option validation,
and reliable exit code behavior.

## Context
This is Day 1 of a 9-day project. By Day 30, you will have a hardened mini-grep
tool. Today you build the CLI interface only - no file scanning or matching yet.

## Specification

Usage:
- `mini-grep [OPTIONS] PATTERN [FILE...]`

Options:
- `-n` : print line numbers in output
- `-i` : case-insensitive matching (ASCII only)
- `-h` : print usage and exit with code 0

Rules:
- If no FILE is given, parse result should indicate stdin mode (`files_count=0`).
- If PATTERN is missing, print usage and exit with code 1.

## Task (45-60 min)
- Implement `cli_parse(argc, argv, &opts)` in `cli.c`.
- Unknown flags must print an error to stderr and exit with code 2.
- Run `make test`.
- Run `make asan`.

## Acceptance criteria
- `make test` passes (0 warnings).
- Clean ASan run.
- `cli_parse` sets all fields correctly for valid argument combinations.
- Answers to all knowledge questions are provided.

## Knowledge check
There are 8 questions in `solution/README.md`.

## Stretch goals
- Support `--` to explicitly end option parsing.
