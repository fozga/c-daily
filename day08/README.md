# Day 08 - Core stdlib algorithms

## Goal
Implement a record sorter and lookup tool using C standard-library algorithms:
`qsort`, `bsearch`, and function pointers.

## What you will build
You will work on a small record management module operating on arrays of
`record_t` structures. The module will sort records in-place and perform fast
lookups using binary search.

## Task (45-60 min)
1. Review `records.h` and understand the `record_t` structure and API.
2. Implement comparator functions and wrapper logic in `records.c`.
3. Implement:
   - `records_sort_by_id`
   - `records_sort_by_name`
   - `records_find_by_id`
4. Run `make test` until all tests pass.
5. Run `make asan`.

## Acceptance criteria
- `make test` passes with zero warnings.
- `make asan` completes with no sanitizer errors.
- Answers to all knowledge questions are completed in `solution/README.md`.

## Knowledge check
There are 8 knowledge-check questions in `solution/README.md`.

## Stretch goals
- Add `records_sort_by_score_desc` for descending score order.
- Implement a generic `records_find` that accepts a function pointer predicate.
