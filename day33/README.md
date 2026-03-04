# Day 33 - Finite State Machines in C

## Goal
Build a table-driven finite state machine for a TCP-like connection sequence.

## Context
FSMs are the backbone of networking and embedded control. You will build a
state machine that handles events without blocking threads.

## Task (45-60 min)
- Review `fsm.h`. States: `CLOSED`, `LISTEN`, `SYN_RCVD`, `ESTABLISHED`.
  Events: `CMD_LISTEN`, `RCV_SYN`, `RCV_ACK`, `CMD_CLOSE`.
- Implement `fsm_dispatch` in `fsm.c`. Instead of a giant `switch/case`,
  use a 2D lookup table: `Transition transitions[NUM_STATES][NUM_EVENTS]`.
- When an event fires, look up the `next_state` and the `action_callback`.
- Update the state and call the callback. Handle invalid transitions
  (return error).
- Run `make test`.

## Acceptance criteria
- `make test` passes (0 warnings).
- Valid event sequences execute callbacks and reach `ESTABLISHED`.
- Invalid events (e.g. `RCV_ACK` while `CLOSED`) are safely rejected.
- Answers to all knowledge questions provided.

## Knowledge check
There are 8 questions in `solution/README.md`.

## Stretch goals
- Implement a transition logging macro that prints
  `[FSM] State X -> Event Y -> State Z`.
