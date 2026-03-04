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

## 6) Example ASan report

### heap-use-after-free

```
==12345==ERROR: AddressSanitizer: heap-use-after-free on address 0x602000000010
READ of size 4 at 0x602000000010 thread T0
    #0 0x55555555528a in process_item faulty_heap.c:47
    #1 0x5555555553f1 in run_workflow faulty_heap.c:91
    #2 0x555555555510 in main faulty_heap.c:120

0x602000000010 was freed by thread T0 here:
    #0 0x7ffff7b9df20 in __interceptor_free
    #1 0x555555555201 in cleanup_item faulty_heap.c:31

previously allocated by thread T0 here:
    #0 0x7ffff7b9de80 in __interceptor_malloc
    #1 0x555555555180 in create_item faulty_heap.c:15
```

### Reading the report

- **Error class**: `heap-use-after-free` — freed memory is accessed again.
- **Access descriptor**: `READ of size 4` — a 4-byte read from an already-freed
  address. The address (`0x602000000010`) sits in a poisoned redzone or
  quarantine region ASan maintains after `free`.
- **Crash stack** (first block): the invalid access is in `process_item` at
  `faulty_heap.c:47`. This is the immediate fault site.
- **Freed stack** ("was freed by"): `cleanup_item` at line 31 freed the object.
  This is the `free()` call that ended the allocation's lifetime.
- **Allocation stack** ("previously allocated by"): `create_item` at line 15
  originally allocated the memory.

Diagnosis workflow:

1. Find the crash stack → understand *what* was accessed.
2. Check the freed stack → find *when* the object's lifetime ended.
3. Check the allocation stack → understand the object's origin and expected
   owner.
4. The root cause is usually a lifetime mismatch: a pointer outlived its object.

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
