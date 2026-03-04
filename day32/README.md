# Day 32 - C11 Threads and Atomics

## Goal
Implement a lock-free Single-Producer Single-Consumer queue using C11 atomics.

## Context
Modern C provides `<stdatomic.h>` for lock-free programming. You will build a
Single-Producer Single-Consumer queue, a common pattern for sending data from
an ISR/hardware thread to a worker thread.

## Task (45-60 min)
- Review `spsc_queue.h`. Notice the `_Atomic` variables for head and tail.
- Implement `sq_push` and `sq_pop` in `spsc_queue.c` using ring-buffer logic
  (modulo capacity).
- Use `atomic_load` and `atomic_store` for safe thread communication.
- Run `make test`. The test spawns 2 threads doing 100,000 operations.

## Acceptance criteria
- `make test` passes (0 warnings).
- No data races or deadlocks.
- Answers to all knowledge questions are provided.

## Knowledge check
There are 8 questions in `solution/README.md`.

## Stretch goals
- Change the atomic operations to use explicit memory models
  (`memory_order_acquire` and `memory_order_release`) instead of sequential
  consistency.
