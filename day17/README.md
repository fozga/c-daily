# Day 17 - Leak hunting with Valgrind

## Goal
Use Valgrind Memcheck to identify and remove multiple categories of memory leaks.

## What you will debug
A multi-step workflow module that appears functionally correct but leaks memory
in several ways.

## Task (45-60 min)
- Run `make test` - it should pass functional checks.
- Run `make valgrind` and inspect the `LEAK SUMMARY`.
- Identify `definitely lost`, `indirectly lost`, and `still reachable` leaks.
- Fix leaks in `leaky_workflow.c` with correct `free()` calls.
- Re-run `make valgrind` until it reports no leaks.

## Acceptance criteria
- Clean `make valgrind` run (`0 bytes` lost in all categories).
- Clean `make asan` run.
- Answers to all knowledge questions are provided.

## Knowledge check
There are 8 questions in `solution/README.md`.

## Stretch goals
Write a simple Valgrind suppression file and test excluding a known
`still reachable` leak.
