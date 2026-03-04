# Day 21 Notes - Defensive and testable C

## 1) Defensive programming in C

Two major tools:
- assertions for developer/invariant bugs
- error codes for runtime/environment/input failures

Use assertions when "this should never happen if code is correct".
Use return values when failures are expected and recoverable (e.g., OOM, bad input).

## 2) `assert()` and `NDEBUG`

`assert(cond)` aborts program when `cond` is false in debug builds.
When `NDEBUG` is defined, assertions are compiled out.

Important rule:
- never put side effects in `assert`, e.g. `assert(do_work() == 0)`.
  In release builds, `do_work()` will not run.

## 3) Data structure invariants

An invariant is a condition that should always hold for a valid structure.

For linked lists, examples:
- count equals actual traversed node count
- list acyclic (optional stronger check)
- empty list implies head == NULL and count == 0

A private verification helper keeps these checks centralized and repeatable.

## 4) Test seams for fault injection

A seam is an indirection point that allows tests to alter behavior.

Allocator seam example:
- production path: `MALLOC_SEAM(size)` -> `malloc(size)`
- test path: configured to fail on Nth allocation

This enables deterministic OOM tests without exhausting system memory.

## 5) Why fault injection matters

OOM branches are hard to hit naturally but critical for robustness.
Without seam-based tests, code may silently crash/leak on rare allocation failures.

## Common mistakes

- Putting side effects in assertions.
- Treating user input errors as assertion failures.
- Forgetting to run invariant checks after mutating operations.
- Writing OOM tests that depend on global machine memory pressure.
- Not resetting seam state between tests.

## C vs C++

- C++ often uses exceptions/RAII to handle failures and cleanup.
- C APIs typically expose explicit success/failure returns.
- Defensive C requires deliberate contracts and test hooks.
