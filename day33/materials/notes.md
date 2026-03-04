# Day 33 Notes - Finite State Machines

## Why use an FSM?

A finite state machine models behavior as:
- a finite set of states
- a finite set of events
- transitions from one state to another

For complex control logic, this is often cleaner than deeply nested `if/else`.
It makes allowed flows explicit and testable.

## Switch-based vs table-driven FSM

### Switch-based
- Easy to start with for tiny systems
- Often becomes long and error-prone as states/events grow
- Harder to audit for missing transition branches

### Table-driven
- Encodes transition rules as data
- Easier to scan coverage of all `(state,event)` pairs
- Usually simpler to extend by adding rows/cells
- Encourages separation between transition rules and execution engine

Tradeoff: table-driven designs can use more static data and need careful enum
index discipline.

## Transition table design in C

A common structure:
- `next_state`
- `action` callback pointer
- `valid` flag

Typical lookup:
1. Validate `current_state` and incoming `event`.
2. Read `transitions[current_state][event]`.
3. If invalid, reject safely.
4. Set `current_state = next_state`.
5. Invoke `action(fsm)` if callback exists.

Using function pointers keeps side effects decoupled from dispatch logic.

## Handling invalid transitions safely

Invalid events happen in real systems (noise, late packet, bad ordering). A
robust FSM must reject unexpected transitions without undefined behavior.

Recommended behavior:
- return failure (`false`)
- keep state unchanged
- optionally log diagnostic information

Never index arrays using unchecked enum values.

## Action callbacks

Callbacks represent transition side effects:
- logging
- counters
- notifying upper layers
- updating external context via `fsm->user_ctx`

Dispatch stays generic while actions remain customizable.

## Common mistakes

- Not checking bounds before indexing transition table with event ID.
- Forgetting to define behavior for invalid `(state,event)` combinations.
- Updating state before validating transition.
- Assuming callback is always non-NULL.
- Mixing side effects into dispatch flow in a non-deterministic order.

## C vs C++ callout

C++ may use richer abstractions (`std::variant`, class-based state objects), but
table-driven FSMs remain valuable even there. In C, explicit enums + struct
tables are lightweight, deterministic, and very suitable for embedded systems.
