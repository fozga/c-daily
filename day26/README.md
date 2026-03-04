# Day 26 - Test matrix for mini-grep

## Goal
Create an integration-test matrix with fixtures, expected outputs, and exit-code
checks for the mini-grep project.

## Context
Day 5 of the project. Today is about quality gates, not new matching features.
You write a shell integration test script rather than C source code.

## Project continuity (required)

Copy your passing Day 25 implementation into `day26/solution/` before running the matrix.
The integration script must validate your cumulative mini-grep, not a fresh scaffold.

## Task (45-60 min)
- Build mini-grep from your Day 22–25 code.
- Review fixture files in `solution/fixtures/`.
- Complete missing cases in `solution/test_matrix.sh`.
- Run: `bash solution/test_matrix.sh ./mini-grep`

## Acceptance criteria
- All tests in `test_matrix.sh` pass.
- Script exits `0` on success and non-zero on failure.
- Answers to all knowledge questions are provided.

## Knowledge check
There are 8 questions in `solution/README.md`.

## Stretch goals
- Add a BATS-based version of the integration tests.
