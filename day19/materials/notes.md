# Day 19 Notes - Hash map with open addressing

## 1) Open addressing vs chaining

### Open addressing
- Data stored directly in array slots.
- Collisions resolved by probe sequence.
- Often good cache locality and fewer heap allocations.

### Chaining
- Each bucket points to list/tree of entries.
- Easier deletion semantics.
- More pointer chasing and allocations.

On modern CPUs, open addressing can be faster for many workloads due to spatial
locality, but it needs careful load factor management.

## 2) Linear probing mechanics

Given hash value `h`, the probe sequence wraps around the array:

### Example — FNV-1a hash and linear probe loop

```c
/* FNV-1a 64-bit hash — fast, good distribution for string keys. */
static uint64_t fnv1a(const char *key) {
    uint64_t h = 14695981039346656037ULL;
    for (const unsigned char *p = (const unsigned char *)key; *p; ++p) {
        h ^= *p;
        h *= 1099511628211ULL;
    }
    return h;
}

/* Linear probe lookup. Returns slot index or -1 if not found. */
static int probe_find(const hashmap_t *m, const char *key) {
    size_t idx = (size_t)(fnv1a(key) % m->capacity);
    for (size_t i = 0; i < m->capacity; ++i) {
        slot_t *s = &m->slots[idx];
        if (s->state == SLOT_EMPTY)   return -1;       /* definitely absent */
        if (s->state == SLOT_LIVE && strcmp(s->key, key) == 0)
            return (int)idx;
        idx = (idx + 1) % m->capacity;                /* wrap around */
    }
    return -1;
}
```

Probe sequence must be identical between `put` and `get`; any deviation
produces silent lookup failures.

## 3) Key ownership and duplication

Map must duplicate keys (`strdup` or `malloc+strcpy`) instead of storing caller
pointer directly, because caller memory might:
- go out of scope
- be mutated
- be freed elsewhere

Owning key copies is essential for safe map lifetime behavior.

## 4) Resizing and rehashing

When `count >= capacity * 0.75`, allocate a larger slot array and reinsert all
live entries using the new capacity's modulo arithmetic.

### Example — why memcpy is wrong

```c
/* WRONG: copies old probe positions which are invalid under new capacity */
memcpy(new_slots, old_slots, old_capacity * sizeof(slot_t));

/* CORRECT: reinsert every live entry so indices are recomputed */
for (size_t i = 0; i < old_capacity; ++i) {
    if (old_slots[i].state == SLOT_LIVE) {
        hashmap_put_into(new_slots, new_capacity,
                         old_slots[i].key, old_slots[i].value);
        /* key is already duplicated; transfer ownership, do not strdup again */
    }
}
```

After the loop, free `old_slots` (not the keys — ownership moved to the new
table). Indices depend entirely on capacity, so they must be recomputed.

## 5) Tombstones for deletion

In linear probing, clearing a slot to empty can break lookup for entries that
were displaced later in probe chain.

Tombstones mark "deleted but probe must continue" state.

Without tombstones, removal can produce false negatives for existing keys.

## Common mistakes

- Forgetting to duplicate key strings.
- Leaking old key on overwrite.
- Forgetting to free keys in destroy.
- Using `memcpy` instead of true rehash on resize.
- Allowing load factor to approach 1.0 and degrading performance badly.

## C vs C++

- C requires explicit ownership handling for key memory.
- C++ `std::unordered_map` generally handles allocation/rehash internally and is
  usually chaining-based.
- In C, correctness depends on explicit probing and cleanup discipline.
