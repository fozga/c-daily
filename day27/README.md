# Day 27 - Performance baseline

## Goal
Benchmark the mini-grep workload, identify likely hotspots, and apply one
measured optimization with before/after data.

## Context
Day 6 of the project. This day focuses on measurement discipline:
measure first, optimize second, then report results.

## Task (45-60 min)
- Build and run `gen_fixture` to generate a 1M-line dataset.
- Run benchmark 5 times and record median wall-clock time.
- Inspect profiling notes and choose one hotspot-oriented change.
- Re-run benchmark with same methodology.
- Record before/after timing in `solution/README.md`.

## Acceptance criteria
- `solution/README.md` includes before/after timing with comparable method.
- One optimization is attempted and evaluated (even if no improvement).
- Answers to all knowledge questions are provided.

## Knowledge check
There are 8 questions in `solution/README.md`.

## Stretch goals
- Run `perf stat ./bench ...` and identify top 3 hotspots.
