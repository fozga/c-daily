# Day 15 - GDB workflow for C bugs

## Goal
Debug a deliberately broken pointer-heavy C routine using a practical GDB flow:
breakpoints, backtrace, and frame inspection.

## What you will debug
A pointer manipulation routine that crashes with a Segmentation Fault. You must
identify the exact line and program state that trigger the crash.

## Task (45-60 min)
- Compile and run with `make test` and watch it crash.
- Run `gdb ./test_runner`.
- Use `run` to trigger the crash inside GDB.
- Use `bt` to inspect the call stack.
- Use `frame` and `print` to inspect variables right before the crash.
- Fix the bug in `broken_pointers.c`.
- Re-run `make test` until all tests pass.

## Acceptance criteria
- `make test` passes (0 warnings, no segfaults).
- `solution/README.md` contains a short GDB bug report (crash line and root cause).
- Answers to all knowledge questions are provided.

## Knowledge check
There are 8 questions in `solution/README.md`.

## Stretch goals
- Use a watchpoint (`watch var_name`) in GDB to detect exactly when a specific
  variable changes value.
