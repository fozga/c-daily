# Day 17 Notes - Leak hunting with Valgrind Memcheck

## 1) Valgrind Memcheck vs AddressSanitizer

Both tools are useful and complementary.

### Memcheck strengths
- Works on many uninstrumented binaries.
- Rich leak categorization (`definitely`, `indirectly`, `possibly`, `still reachable`).
- Excellent diagnostics for uninitialized value usage.

### ASan strengths
- Usually faster runtime overhead than Memcheck.
- Strong stack/global bounds checking via compiler instrumentation.
- Detailed allocation/free traces with sanitizer runtime.

Using both catches more classes of problems than either alone.

## 2) The 4 leak categories in Valgrind

### Definitely lost
No pointer to the allocation remains. This is a true leak and must be fixed.

### Indirectly lost
Allocation is reachable only through another leaked block. Fixing the parent
leak often removes indirectly lost children automatically.

### Possibly lost
Valgrind only sees interior pointers or ambiguous references; ownership is
unclear. Needs careful analysis.

### Still reachable
Pointer still exists at process exit, so memory could theoretically be freed.
May indicate missing cleanup in shutdown paths.

## 3) Uninitialized value errors

A common message:
- `Conditional jump or move depends on uninitialised value(s)`

This means control flow used data that was never initialized. The value may come
from stack, heap, or struct fields left unset.

Use:
- `--track-origins=yes`

to get origin traces for where uninitialized bytes first appeared.

## 4) Reading Memcheck output effectively

Typical reading order:
1. First invalid access/error message.
2. Stack trace at error point.
3. Allocation/free origin stacks.
4. Final leak summary categories.

For leaks:
- Start with `definitely lost`.
- Then revisit `indirectly lost`.
- Resolve `still reachable` by explicit subsystem shutdown cleanup.

## 5) Cleanup best practices in C

- Define ownership clearly for every allocated object.
- Pair every successful allocation path with cleanup path.
- Use a single `goto cleanup` section for complex functions.
- Free nested members before freeing container struct.
- Set pointers to `NULL` after free when appropriate.

## 6) Example Valgrind output

Typical Valgrind invocation for leak analysis:

```
valgrind --leak-check=full --show-leak-kinds=all \
         --track-origins=yes --error-exitcode=1 ./test_runner
```

### Uninitialized value error

```
==23456== Conditional jump or move depends on uninitialised value(s)
==23456==    at 0x10916D: process_node (leaky_workflow.c:58)
==23456==    by 0x109270: run_workflow (leaky_workflow.c:91)
==23456==  Uninitialised value was created by a heap allocation
==23456==    at 0x4C2FB0F: malloc (in /usr/lib/valgrind/...)
==23456==    by 0x1090AC: create_node (leaky_workflow.c:22)
```

Reading this: a field inside the struct returned by `create_node` was never
written. `--track-origins=yes` traces the uninitialized bytes back to the
`malloc` call at line 22. Fix: zero the struct after allocation
(`memset(p, 0, sizeof(*p))`) or initialize every field explicitly.

### Leak summary

```
==23456== LEAK SUMMARY:
==23456==    definitely lost: 48 bytes in 3 blocks
==23456==    indirectly lost: 192 bytes in 12 blocks
==23456==      possibly lost: 0 bytes in 0 blocks
==23456==    still reachable: 16 bytes in 1 blocks
==23456==         suppressed: 0 bytes in 0 blocks
```

Reading order:

1. Fix `definitely lost` first — no live pointer refers to these blocks; they
   are unrecoverable true leaks.
2. `indirectly lost` usually disappears once its parent block is freed.
3. Investigate `still reachable` — the pointer exists at exit but the subsystem
   never calls its shutdown/cleanup function.
4. `possibly lost` needs manual analysis (interior pointers or ambiguous
   references).

## Common mistakes

- Freeing only outer struct but not internal heap fields.
- Overwriting pointers before freeing old allocation.
- Assuming process exit is acceptable cleanup for libraries.
- Ignoring `still reachable` because tests pass functionally.
- Forgetting `--track-origins=yes` when debugging uninitialized data.

## C vs C++

- C has no destructors/RAII by default; cleanup is explicit and manual.
- C++ developers often rely on smart pointers/containers to automate ownership.
- In C, API design must encode ownership transfer clearly to avoid leaks.
