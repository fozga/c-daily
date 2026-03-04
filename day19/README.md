# Day 19 - Hash map in pure C

## Goal
Implement a string-key hash map using open addressing, linear probing, and
resize by load factor.

## What you will build
A `const char* -> int` map with collision resolution by linear probing and
automatic growth when load factor reaches threshold.

## Task (45-60 min)
- Review `hashmap.h`.
- Implement map operations in `hashmap.c` (FNV-1a hash is provided).
- Handle collisions by probing forward.
- Implement rehashing when `count >= capacity * 0.75`.
- Run `make test`.
- Run `make asan` and `make valgrind`.

## Acceptance criteria
- `make test` passes with 0 warnings.
- Clean ASan and Valgrind runs.
- Answers to all knowledge questions are provided.

## Knowledge check
There are 8 questions in `solution/README.md`.

## Stretch goals
Implement `hashmap_remove` using tombstones for deletion without breaking probe
chains.
