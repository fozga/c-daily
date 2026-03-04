# 35-Day Interactive C Course (Linux)

Repository scaffold for a 5-week C learning path on Linux. Each day has its own folder, learning materials, and a `solution/` workspace where you add your own code.

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

## 35-Day Plan (concise)

- Days 01-05: C basics (types, operators, control flow, functions)
- Days 06-10: arrays, strings, pointers foundations
- Days 11-15: memory management, structs, modular code
- Days 16-20: file I/O, error handling, command-line programs
- Days 21-25: advanced pointers, dynamic structures, debugging
- Days 26-35: mini-projects, performance tuning, and advanced C systems topics (memory pools, atomics, FSMs, ring buffers, callbacks)

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
- `day01` ... `day35`
  - `README.md` - day task and acceptance criteria
  - `materials/` - short notes, links, checklist
  - `solution/` - your implementation area

## Detailed Table of Contents (c-drills)

| Day | Topic | Key Concepts | Task Type | Task Description | Builds On |
|---|---|---|---|---|---|
| day01 | GCC and Make workflow | compilation units, linker, Make targets | implement | Set up `c-drills` build flow by compiling a multi-file C11 program with strict debug flags and a `test/asan/valgrind` Make interface. | Establishes daily toolchain used throughout the course. |
| day02 | Integer model and UB traps | integer promotions, signed overflow UB, size_t | debug | Diagnose and fix a numeric utility that fails due to implicit conversions and overflow assumptions. | Reuses day01 build pipeline to inspect real compiler diagnostics. |
| day03 | Pointers, objects, lifetime | address semantics, aliasing, storage duration | implement | Implement pointer-based swap, slice, and in-place transform helpers without relying on C++ references. | Applies day02 type rules to memory addresses and object lifetimes. |
| day04 | Arrays and pointer arithmetic | contiguous memory, bounds discipline, decay rules | implement | Build a fixed-buffer parser that walks arrays via pointers while enforcing explicit bounds checks. | Extends day03 pointer mechanics to safe traversal patterns. |
| day05 | C strings without std::string | NUL terminator, buffer length, copying contracts | implement | Implement `strview`-style operations (find, trim, split) over `char*` plus length to avoid unsafe C-string assumptions. | Builds on day04 bounds logic for byte-oriented text data. |
| day06 | Heap ownership in C | malloc/free, ownership transfer, double free | implement | Implement a dynamic line buffer API with explicit create/destroy functions and documented ownership rules. | Adds heap management to day05 text processing primitives. |
| day07 | API contracts and error model | header contracts, errno, return codes | refactor | Refactor earlier utilities into a small C library with clear headers, invariant checks, and error-reporting conventions. | Consolidates days01-06 into reusable module-style APIs. |
| day08 | Core stdlib algorithms | qsort, bsearch, function pointers | implement | Implement a record sorter and lookup tool using `qsort`/`bsearch` with custom comparators. | Reuses day07 modular API style with standard-library callbacks. |
| day09 | Robust text input parsing | fgets, strtol, sscanf, validation | implement | Build a CLI parser that reads mixed numeric/text records and reports malformed lines precisely. | Extends day08 data processing with safer input ingestion. |
| day10 | Binary I/O and layouts | fopen modes, fread/fwrite, endian awareness | implement | Implement a binary record serializer/deserializer with explicit format version and sanity checks. | Evolves day09 parsers from text streams to binary formats. |
| day11 | Preprocessor as code generator | macros, include guards, conditional compilation | refactor | Introduce macro-based helpers for repetitive checks while eliminating unsafe macro side effects. | Refactors day10 codebase using disciplined preprocessor patterns. |
| day12 | Struct design and memory layout | padding, alignment, packed pitfalls | debug | Investigate and fix a struct layout bug that breaks binary compatibility across builds. | Uses day10 binary format knowledge plus day11 compile-time controls. |
| day13 | Module boundaries in C | opaque types, translation units, encapsulation | refactor | Split a monolithic utility into `api.h` and private implementation files with opaque handles. | Turns day12 data structures into maintainable module boundaries. |
| day14 | Mini library integration day | static library, public API, smoke tests | implement | Assemble previous components into a small reusable C library and a CLI consumer exercising all APIs. | Integrates week2 concepts into one coherent, testable package. |
| day15 | GDB workflow for C bugs | breakpoints, watchpoints, backtrace, frames | debug | Debug a deliberately broken pointer-heavy program in GDB and document root cause plus fix. | Uses day14 integrated code as realistic debugging target. |
| day16 | Catch memory bugs with ASan | use-after-free, stack overflow, redzones | debug | Run ASan on faulty heap code, fix reported defects, and harden allocation/free paths. | Continues day15 debugging with sanitizer-driven evidence. |
| day17 | Leak hunting with Valgrind | leak kinds, invalid read/write, suppression basics | debug | Analyze Valgrind output for a multi-allocation workflow and remove all definite leaks. | Complements day16 by validating runtime memory hygiene. |
| day18 | Singly linked list from scratch | node ownership, traversal, insert/delete | implement | Implement a generic singly linked list API with clear ownership semantics and failure-safe operations. | Applies memory-discipline from days16-17 to dynamic structures. |
| day19 | Hash map in pure C | open addressing, hashing, tombstones, resize | implement | Implement a string-key hash map with linear probing, deletion markers, and load-factor growth. | Builds on day18 dynamic allocation and API contract practices. |
| day20 | Bitset and flag operations | bitwise ops, masks, compact storage | implement | Implement a dynamic bitset module for set/clear/test and bulk operations on large boolean domains. | Adds compact data representation to day19 structure toolkit. |
| day21 | Defensive and testable C | assertions, invariants, fault injection, seams | refactor | Add defensive checks and test seams to list/map/bitset modules so failures are observable and reproducible. | Hardens days18-20 data structures before project phase. |
| day22 | Final project: CLI skeleton | argv parsing, usage UX, exit codes | project | Start a mini-grep CLI project by implementing argument parsing, option validation, and structured error exits. | Reuses day21 defensive style in a user-facing tool. |
| day23 | Final project: match engine v1 | line scanning, pattern state, match reporting | project | Implement the core matcher for literal and dot-wildcard patterns over streamed text lines. | Plugs into day22 CLI to produce first working search results. |
| day24 | Final project: file traversal | stdin/files, buffered reading, path handling | project | Extend mini-grep to process multiple files and stdin uniformly with consistent output formatting. | Expands day23 engine from single input to realistic workflows. |
| day25 | Final project: diagnostics hardening | errno mapping, partial failures, resilience | project | Add robust diagnostics so unreadable files and malformed options report actionable errors without crashing. | Strengthens day24 multi-file behavior for production-like robustness. |
| day26 | Final project: test matrix | edge cases, regression tests, golden outputs | project | Create a focused test matrix covering corner cases, regressions, and expected CLI outputs. | Formalizes quality gates around day22-25 functionality. |
| day27 | Final project: performance baseline | timing methodology, hotspots, I/O costs | benchmark | Benchmark key workloads, identify bottlenecks, and apply one measured optimization with before/after data. | Optimizes the stabilized implementation from day26. |
| day28 | Project series I: regex-lite sets | character classes, escapes, parser extension | project | Extend matcher syntax with bracket character classes and escape handling while preserving old behavior. | Begins 3-part expansion on top of day27 optimized core. |
| day29 | Project series II: parallel scan | C11 threads, work partitioning, synchronization | project | Add optional parallel file scanning using C11 threads with deterministic output and safe shared state. | Builds directly on day28 parser/matcher to scale throughput. |
| day30 | Project series III: release polish | hardening, packaging, docs, final review | project | Finalize mini-grep with polish pass, stress tests, release notes, and a retrospective on design trade-offs. | Completes day28-29 expansion into a deliverable CLI tool. |
| day31 | Static Memory Pools | fixed-size allocation, no-malloc | implement | Build a fixed-size block allocator to avoid heap fragmentation in constrained contexts. | Applies strict memory constraints to previous dynamic structures. |
| day32 | C11 Threads and Atomics | <threads.h>, <stdatomic.h>, SPSC | implement | Implement a Single-Producer Single-Consumer queue using C11 atomics and threads. | Replaces C++ std::thread with C11 standard concurrency primitives. |
| day33 | Finite State Machines | transition tables, state enum | implement | Implement a robust FSM for a simulated device initialization sequence. | Reuses function pointer knowledge for control flow. |
| day34 | Circular Ring Buffers | modulo arithmetic, lock-free | implement | Build a fast, array-backed ring buffer for streaming bytes. | Extends array manipulation skills to infinite streams. |
| day35 | Callbacks and Interrupts | event dispatch, sig_atomic_t | implement | Wire up an event dispatcher handling simulated asynchronous events. | Combines state machines, function pointers, and async signals. |

## Theme weeks

**Week 1** establishes C-specific foundations for someone coming from C++: strict toolchain discipline, undefined behavior awareness, pointer/array realities, C-string constraints, manual heap ownership, and explicit API contracts. The learner writes code daily but mostly learns to think in terms of memory and contracts instead of abstractions like RAII or exceptions.

**Week 2** shifts into practical C ecosystem work: standard-library usage patterns, preprocessor discipline, robust text/binary I/O, and data layout awareness. The week ends with modular design and integration, so the learner stops writing isolated snippets and starts building maintainable C components.

**Week 3** is about reliability under pressure: debugger-first diagnosis, sanitizer-guided bug fixing, leak analysis, and data-structure implementation with defensive practices. By the end of the week, the learner has both implementation muscle (list/hash-map/bitset) and a repeatable quality workflow.

**Week 4** turns skills into a coherent CLI project (mini-grep) that grows incrementally from a skeleton to a hardened tool. The week combines feature evolution, rigorous integration testing (shell scripts), and performance benchmarking to mirror real systems programming practice.

**Week 5** dives into advanced systems and embedded-style patterns. The focus shifts to deterministic memory (static pools instead of `malloc`), standard C11 concurrency (threads and atomics), and asynchronous control flow (finite state machines, ring buffers, and callback-driven event loops).

## Learning outcomes

- Build and run multi-file C11 programs with strict warning/debug flags using GCC and Make.
- Identify and avoid common C undefined-behavior traps around integer conversions and pointer misuse.
- Design C APIs with explicit ownership, lifetime, and error-reporting contracts.
- Implement safe text and binary I/O paths with validation and robust failure handling.
- Diagnose complex runtime defects with GDB, AddressSanitizer, and Valgrind.
- Implement and test core data structures (linked list, hash map, bitset, ring buffer) in idiomatic C.
- Write defensive, testable C modules using invariants, test seams, and integration test scripts.
- Develop, benchmark, and harden a non-trivial Linux CLI tool end-to-end.
- Apply systems-level patterns: fixed-size memory pools, table-driven state machines, and callback dispatchers.
- Write concurrent C code using the C11 `<threads.h>` and `<stdatomic.h>` standards without relying on C++ `std::thread`.
