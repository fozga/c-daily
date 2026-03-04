# 30-Day Interactive C Course (Linux)

Repository scaffold for a 30-day C learning path on Linux. Each day has its own folder, learning materials, and a `solution/` workspace where you add your own code.

## Requirements

- Linux
- GCC (supporting `-std=c11`)
- GNU Make
- Valgrind (for memory checks)

## Quick Start

1. Pick a day, e.g. `day=01`.
2. Write your solution in `dayNN/solution/`.
3. Run from repository root:

```bash
make day=01 test
make day=01 asan
make day=01 valgrind
make day=01 clean
```

## Dispatcher Commands (root Makefile)

- `make day=NN test` - compile and run tests for day `NN`
- `make day=NN asan` - compile with AddressSanitizer and run tests
- `make day=NN valgrind` - run tests under Valgrind leak checker
- `make day=NN clean` - clean build artifacts for day `NN`

## Compiler Standard and Quality Flags

The default setup in each day uses:

- `-std=c11` - compile as C11 standard.
- `-O0` - disable optimizations to simplify debugging.
- `-g` - include debug symbols for debuggers (`gdb`) and better stack traces.
- `-Wall` - enable common warnings.
- `-Wextra` - enable additional useful warnings.
- `-Wpedantic` - enforce strict standard compliance warnings.
- `-Werror` - treat warnings as errors to keep code quality high.

## 30-Day Plan (concise)

- Days 01-05: C basics (types, operators, control flow, functions)
- Days 06-10: arrays, strings, pointers foundations
- Days 11-15: memory management, structs, modular code
- Days 16-20: file I/O, error handling, command-line programs
- Days 21-25: advanced pointers, dynamic structures, debugging
- Days 26-30: mini-projects, optimization basics, final review

## Submission / Review Rules

For each day:

1. Implement your solution in `dayNN/solution/`.
2. Ensure `make day=NN test` passes.
3. Ensure `make day=NN asan` passes (no ASan errors).
4. Ensure `make day=NN valgrind` reports no leaks.
5. Commit your changes with a clear message.

Suggested commit style:

```text
dayNN: solve task and pass test/asan/valgrind
```

## Repository Layout

- `README.md` - general instructions and workflow
- `Makefile` - root dispatcher to day-specific makefiles
- `day01` ... `day30`
  - `README.md` - day task and acceptance criteria
  - `materials/` - short notes, links, checklist
  - `solution/` - your implementation area
