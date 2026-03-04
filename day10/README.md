# Day 10 - Binary I/O and layouts

## Goal
Implement binary record serialization/deserialization using `fread`/`fwrite`,
fixed-width integer types, and explicit format validation.

## What you will build
A binary file format for an array of records with a fixed header:
magic bytes, version, and record count.

## Task (45-60 min)
1. Review `binrec.h` and understand the header layout.
2. Implement `binrec_write` and `binrec_read` in `binrec.c`.
3. Use fixed-width integer types (`uint32_t`, `int32_t`) for deterministic layout.
4. Run `make test` and verify write/read round-trip correctness.
5. Run `make asan`.

## Acceptance criteria
- `make test` passes with zero warnings.
- `make asan` reports no sanitizer issues.
- Bad magic bytes and version mismatches are detected and rejected.
- Answers to all knowledge questions are completed in `solution/README.md`.

## Knowledge check
There are 8 knowledge-check questions in `solution/README.md`.

## Stretch goals
Add helpers that normalize integer fields to little-endian on write and convert
back on read for a portable on-disk format.
