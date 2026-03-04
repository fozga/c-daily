# Day 29 - Parallel file scanning with C11 threads

## Goal
Add optional parallel scanning using C11 threads and safe shared-state updates.

## Context
Day 8 of the project. Instead of scanning files one by one, we use worker
threads. Each worker pulls the next file from a shared queue and contributes to
a global match counter.

## Task (45-60 min)
- Review `parallel_scanner.h`.
- Implement thread dispatch in `parallel_scanner.c` with `<threads.h>`:
  `thrd_create`, `mtx_lock`, `mtx_unlock`, `thrd_join`.
- Protect both shared file index and shared total counter with `mtx_t`.
- Run `make test` and verify exact total.
- Run `make asan`.

## Acceptance criteria
- `make test` passes with 0 warnings.
- Global match count is exactly correct every run.
- Answers to all knowledge questions are provided.

## Knowledge check
There are 8 questions in `solution/README.md`.

## Stretch goals
- Replace mutex-protected total with `<stdatomic.h>` counter.
