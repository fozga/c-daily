# Day 13 Notes - Opaque module design in C

## 1) Opaque pointer pattern

Public header:
- forward-declare struct type
- expose only pointer handle and API functions

Example pattern:
- `typedef struct store store_t;`

Private definition lives in `.c` (or private header consumed only by `.c`).

Benefits:
- consumers cannot access internal fields directly
- easier to maintain invariants
- internal data structure can change without API breakage

## 2) Why hiding internals matters

If internals are public:
- callers can mutate fields illegally
- invariants become impossible to enforce
- changing layout can break ABI or dependent code

Opaque types protect implementation freedom and reduce coupling.

## 3) Translation unit boundaries and `static`

In C, each `.c` file is a translation unit.

`static` at file scope gives internal linkage:
- symbol is visible only inside that translation unit
- helps avoid namespace collisions
- communicates implementation-private helpers

Use `static` for helper functions and private globals in module `.c` files.

## 4) Public vs private headers

### Public header (`store.h`)
- stable API declarations
- opaque handle typedef
- required standard includes only

### Private header (`store_internal.h`)
- internal structs/constants
- implementation-only helpers
- included by module `.c`, not by consumers/tests

### Implementation (`store.c`)
- includes both headers
- owns allocation and mutation logic

## 5) Tradeoffs of opaque handles

Pros:
- strong encapsulation
- ABI flexibility
- better API boundaries

Cons:
- heap allocation often required
- pointer indirection overhead
- more boilerplate for lifecycle management

For tiny POD-like data passed by value, a public struct can sometimes be
simpler. Choose based on stability and encapsulation needs.

## Common mistakes

- Exposing struct internals in public headers.
- Including private header in consumer code/tests.
- Forgetting NULL checks in API functions.
- Leaking allocations on error paths.
- Returning pointers into internal storage without lifetime documentation.
- Failing to keep `count`/capacity invariants consistent.

## C vs C++

- Opaque C handles resemble C++ PIMPL in spirit.
- C++ classes provide `private:` access control at language level.
- In C, encapsulation is convention + header boundaries + linker visibility.
