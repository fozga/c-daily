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
