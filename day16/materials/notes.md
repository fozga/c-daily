# Day 16 Notes - Catching memory bugs with AddressSanitizer

## 1) How ASan works

AddressSanitizer instruments your program at compile time and tracks memory
validity using shadow memory plus redzones around objects.

Key ideas:
- **Shadow memory** stores metadata about real memory accessibility.
- **Redzones** are poisoned bytes around allocations/stack objects that trap
  out-of-bounds accesses.
- Runtime interceptors wrap allocation APIs to track lifetimes.

Typical compile flags:
- `-fsanitize=address`
- `-fno-omit-frame-pointer` for clearer stack traces
- debug symbols (`-g`) for line-level diagnostics

## 2) Anatomy of an ASan report

A report usually includes:
- Error class (`heap-use-after-free`, `heap-buffer-overflow`, etc.)
- Access type (`READ`/`WRITE`) and byte size
- Crash stack trace (where invalid access happened)
- Allocation stack trace (where memory came from)
- Free stack trace (for use-after-free cases)

You should answer:
1. What memory object was accessed incorrectly?
2. Is the bug bounds, lifetime, or stack-return related?
3. Which code path introduced the invalid state?

## 3) Common ASan bug classes

### Heap use-after-free
Code accesses heap memory after `free()`.

### Heap buffer overflow
Code reads/writes beyond allocated heap range (including off-by-one NUL writes).

### Stack buffer overflow
Code accesses beyond local array bounds.

### Stack use-after-return
Code stores/returns pointer to local stack object that no longer exists.

## 4) ASan vs Valgrind (practical differences)

ASan strengths:
- Very fast compared to Valgrind.
- Great stack/global out-of-bounds detection.
- Precise allocation/free context in many cases.

Valgrind strengths:
- No recompilation needed for many binaries.
- Rich leak categorization and uninitialized value diagnostics.

In practice, use both in CI/debug workflows.

## 5) Performance and deployment

ASan adds runtime overhead (often 1.5x-3x) and memory overhead. It is intended
for testing/debug builds, not usually production binaries.

## Common mistakes

- Forgetting `-fno-omit-frame-pointer` and getting poor traces.
- Running only non-ASan tests and missing latent memory corruption.
- "Fixing" symptom lines without tracing allocation/free origin stacks.
- Assuming passing tests imply memory safety.
- Leaving sanitizer flags enabled in release artifacts unintentionally.

## C vs C++

- ASan catches the same classes in both languages, but C++ adds lifetimes for
  objects, RAII interactions, and operator new/delete paths.
- In C, manual lifetime management is explicit, so ASan reports often map
  directly to raw pointer misuse.
