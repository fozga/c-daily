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

Given hash value `h`:
- `index = h % capacity`
- If occupied by different key: `index = (index + 1) % capacity`
- Continue until matching key or empty slot

Probe sequence must be consistent between put/get.

## 3) Key ownership and duplication

Map must duplicate keys (`strdup` or `malloc+strcpy`) instead of storing caller
pointer directly, because caller memory might:
- go out of scope
- be mutated
- be freed elsewhere

Owning key copies is essential for safe map lifetime behavior.

## 4) Resizing and rehashing

When load factor grows (e.g. >= 0.75), allocate a bigger slot array and reinsert
all existing entries with new `% new_capacity` math.

Important: you cannot `memcpy` old table and expect probing structure to remain
valid. Indices depend on capacity.

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
