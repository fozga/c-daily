# Day 13 Notes - Opaque module design in C

## 1) Opaque pointer pattern

Public header:
- forward-declare struct type
- expose only pointer handle and API functions

Private definition lives in `.c` (or private header consumed only by `.c`).

Benefits:
- consumers cannot access internal fields directly
- easier to maintain invariants
- internal data structure can change without API breakage

### Example

```c
/* ---- store.h (public API — ships to consumers) ---- */
#ifndef STORE_H
#define STORE_H
#include <stddef.h>

typedef struct store store_t;   /* forward declaration only — size unknown */

store_t *store_create(size_t capacity);
void     store_destroy(store_t *s);          /* safe to call with NULL     */
int      store_set(store_t *s, const char *key, int value);
int      store_get(const store_t *s, const char *key, int *out_value);

#endif /* STORE_H */


/* ---- store_internal.h (private — included ONLY by store.c) ---- */
#ifndef STORE_INTERNAL_H
#define STORE_INTERNAL_H
#include "store.h"

#define STORE_MAX_ENTRIES 256

typedef struct {
    char key[64];
    int  value;
    int  occupied;
} store_entry_t;

struct store {                  /* full definition: consumers never see this */
    store_entry_t entries[STORE_MAX_ENTRIES];
    size_t        count;
    size_t        capacity;
};

#endif /* STORE_INTERNAL_H */


/* ---- store.c (implementation) ---- */
#include "store_internal.h"     /* includes both headers transitively */
#include <stdlib.h>
#include <string.h>

store_t *store_create(size_t capacity) {
    store_t *s = calloc(1, sizeof *s);
    if (s) s->capacity = capacity < STORE_MAX_ENTRIES
                         ? capacity : STORE_MAX_ENTRIES;
    return s;
}

void store_destroy(store_t *s) {
    free(s);   /* free(NULL) is safe; no NULL check needed */
}

/* ---- tests.c (consumer) ---- */
/* #include "store_internal.h"  <-- FORBIDDEN: breaks encapsulation */
#include "store.h"              /* only public API is needed         */

void test_basic(void) {
    store_t *s = store_create(16);
    store_set(s, "key1", 42);
    int v;
    store_get(s, "key1", &v);   /* v == 42 */
    store_destroy(s);
    /* s->count;  <-- compile error: incomplete type 'store_t' — by design */
}
```

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

```c
/* store.c — these helpers are invisible outside this translation unit */

static size_t hash_key(const char *key, size_t capacity) {
    size_t h = 5381;
    while (*key) h = h * 33 ^ (unsigned char)*key++;
    return h % capacity;
}

static store_entry_t *find_entry(store_t *s, const char *key) {
    size_t idx = hash_key(key, s->capacity);
    /* linear probe — implementation detail, never exposed in store.h */
    for (size_t i = 0; i < s->capacity; i++) {
        store_entry_t *e = &s->entries[(idx + i) % s->capacity];
        if (!e->occupied) return NULL;
        if (strcmp(e->key, key) == 0) return e;
    }
    return NULL;
}
/* Without 'static', hash_key and find_entry would be exported symbols
   and could collide with functions of the same name in other modules. */
```

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
