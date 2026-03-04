# Day 35 Notes - Callbacks, Dispatch, and Interrupt Flags

## Callbacks in C

A callback is a function pointer provided by the caller and invoked later by a
framework/module. In C, a common event callback signature is:

`void (*fn)(int event_id, void* ctx)`

For this day we include payload data too:
- `event_id` identifies what happened
- `event_data` carries event-specific values
- `ctx` is caller-owned state (closure substitute)

Because C has no capturing lambdas, `void* ctx` is the standard way to bind
state to callback behavior.

## Event dispatcher pattern (Observer in C)

A dispatcher maintains a registry of subscribers:
- event type
- callback function
- callback context

When an event fires, dispatcher iterates registered slots and invokes callbacks
matching that event.

This is the Observer pattern in procedural form:
- publisher does not know concrete subscribers
- subscribers can be added without changing publisher logic

## ISR context and main loop cooperation

In embedded systems, Interrupt Service Routines (ISRs) can preempt normal code.
Often an ISR must be very short and only signal work to be processed later.

A common pattern:
1. ISR sets a flag.
2. Main loop polls flag.
3. Main loop exits/handles deferred work.

## `volatile` and `sig_atomic_t`

If a flag can change asynchronously (signal/ISR style), compiler optimizations
may otherwise cache it in a register and never reload it in loops.

`volatile` tells compiler each read/write is observable and must occur.

`sig_atomic_t` from `<signal.h>` guarantees atomic read/write for that scalar
type in asynchronous signal contexts.

Typical declaration:

`static volatile sig_atomic_t g_exit_requested;`

Then:
- callback/ISR sets it
- main loop checks it

## Safety note for real ISRs

Real hardware ISRs (or POSIX signal handlers) must avoid non-async-signal-safe
functions such as `printf`, `malloc`, and many library calls. Keep handlers
minimal: set flags, capture lightweight data, return.

## Common mistakes

- Forgetting `volatile` on shared exit flags.
- Using a plain `bool` flag modified asynchronously.
- Calling heavy/unsafe APIs directly inside ISR-like callback paths.
- Not checking callback pointer for NULL before invocation.
- Mutating callback registry while iterating without a plan.

## C vs C++ callout

C++ offers `std::function`, lambdas with captures, and richer event abstractions.
C uses raw function pointers plus `void* ctx`, which is less ergonomic but very
explicit and efficient for low-level systems.
