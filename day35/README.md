# Day 35 - Callbacks and Event Dispatchers

## Goal
Wire up an event dispatcher handling simulated asynchronous events.

## Context
The final day! You will build an event dispatcher that routes simulated
hardware interrupts or UI events to registered callback functions, passing a
`void* user_ctx` to maintain state.

## Task (45-60 min)
- Review `dispatcher.h`.
- Implement `dispatch_register` to save a function pointer and context in an
  array.
- Implement `dispatch_fire_event` to iterate the array and call the functions
  that match the `event_id`.
- Implement a mechanism where a specific callback sets a global
  `volatile sig_atomic_t` flag to signal the main loop to exit.
- Run `make test`.

## Acceptance criteria
- `make test` passes (0 warnings).
- Callbacks receive the correct `user_ctx`.
- Answers to all knowledge questions provided.

## Knowledge check
There are 8 questions in `solution/README.md`.

## Course completion
Congratulations on finishing the full 35-day C drill. You just covered core C
systems fundamentals, debugging workflows, low-level data structures, and
concurrency patterns used in production environments.
