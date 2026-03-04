# Day 14 Notes - Static library integration and CLI wiring

## 1) Static libraries vs shared libraries

### Static library (`.a`)
- Archive of object files (`.o`) built with `ar`.
- Linked into final executable at link time.
- Increases executable size but simplifies deployment.

### Shared library (`.so`)
- Loaded at runtime by dynamic linker.
- Smaller executables and shared code in memory.
- Requires runtime library availability and ABI compatibility management.

When static linking is useful:
- simple deployment environments
- reproducible toolchains
- educational projects and self-contained binaries

## 2) How `ar` works

Typical command:
- `ar rcs libcdrills.a file1.o file2.o ...`

Flags:
- `r`: insert/replace members
- `c`: create archive if missing
- `s`: write index (symbol table) for faster linking

## 3) Link order matters

GNU linker resolves symbols left-to-right.

If library appears before objects that reference it, unresolved symbols can
remain unresolved.

Good pattern:
- `gcc main.o ... -L. -lcdrills`

Potentially bad pattern:
- `gcc -L. -lcdrills main.o`

## 4) Umbrella headers

An umbrella header (like `cdrills_lib.h`) re-exports multiple module headers.

Benefits:
- one include for consumers
- clear top-level API surface

Tradeoffs:
- broader recompilation when umbrella changes
- may expose more APIs than a minimal consumer needs
- module boundaries can blur if overused

## 5) CLI dispatch in C

Typical flow:
1. validate `argc`
2. read `argv[1]` as command
3. route via `strcmp`
4. return standard exit codes (`0` success, nonzero failure)

Keep each subcommand in a helper function for readability and testing.

## 6) Integration tests vs unit tests

Unit tests:
- isolate one function/module

Integration smoke tests:
- exercise cross-module behavior
- catch link issues, API mismatches, and boundary contract bugs

For library assembly day, smoke tests are essential because build/link contracts
are part of correctness.

## Common mistakes

- Forgetting to include all required object files in the archive.
- Wrong link order when building CLI/tests.
- Missing `.PHONY` declarations for non-file targets.
- Coupling tests to private headers instead of public API.
- Assuming integration works because unit tests passed independently.

## C vs C++

- C often uses Make + `ar` directly for small libraries.
- C++ projects often use larger build systems with richer dependency modeling.
- Fundamentals are the same: archive objects, expose stable headers, link in
  correct order, and test integration end-to-end.
