# Day 06 Notes - Heap Ownership in C

This day is about making ownership explicit in APIs. In C, memory safety is mostly a contract discipline problem: if the contract is unclear, leaks and invalid frees follow quickly.

## 1) The C heap API: `malloc`, `calloc`, `realloc`, `free`

- `malloc(size)` allocates an uninitialized block of `size` bytes.
- `calloc(count, size)` allocates `count * size` bytes and zero-initializes them.
- `realloc(ptr, new_size)` resizes a previously allocated block.
- `free(ptr)` releases heap memory allocated by `malloc`/`calloc`/`realloc`.

Allocation functions return `NULL` on failure. `free(NULL)` is safe and does nothing.

### Example

```c
char* p = (char*)malloc(16);
if (p == NULL) {
    return false;
}

p[0] = 'A';
p[1] = '\0';

free(p);
p = NULL;
```

### Common mistakes

- Assuming allocated memory is automatically initialized when using `malloc`.
- Forgetting that `realloc` may move memory to a new address.
- Freeing memory not obtained from the heap allocator.

> **C vs C++:** C uses explicit heap APIs and manual cleanup. C++ has `new`/`delete`, smart pointers, and standard containers that often hide allocation details.

## 2) Ownership semantics in C

Ownership answers: who must eventually call `free`? Since C has no destructors, ownership must be documented in function contracts.

Typical patterns:

- **Caller owns output**: API returns allocated pointer; caller must free.
- **Callee owns internal storage**: API returns borrowed pointer valid until next mutation/destroy.
- **Transfer of ownership**: function explicitly hands pointer ownership to another layer.

Document lifetime and free-responsibility in comments and naming.

### Example

```c
/* Caller owns returned buffer and must free it. */
char* read_line_owned(FILE* f);

/* Borrowed pointer: do not free, invalid after next append/destroy. */
const char* dstr_get_cstr(const dyn_string_t* ds);
```

### Common mistakes

- Returning heap memory without stating who frees it.
- Returning borrowed memory but caller treats it as owned.
- Destroying object while borrowed pointer is still in use elsewhere.

> **C vs C++:** RAII in C++ ties cleanup to object lifetime automatically. In C, ownership must be explicit and enforced by code review/tests.

## 3) `realloc` pitfalls and failure behavior

If `realloc(old_ptr, new_size)` fails, it returns `NULL` and **does not free old_ptr**. The old block remains valid.

This is why this pattern is dangerous:

```c
ptr = realloc(ptr, new_size);
```

If `realloc` returns `NULL`, you lose the only pointer to old memory, causing a leak.

Use a temporary pointer:

### Example

```c
void* tmp = realloc(ptr, new_size);
if (tmp == NULL) {
    /* ptr still valid here */
    return false;
}
ptr = tmp;
```

### Common mistakes

- Assigning `realloc` directly to the live pointer.
- Forgetting to update metadata (`capacity`) after successful growth.
- Assuming `realloc` always preserves address identity.

> **C vs C++:** `std::vector` growth handles reallocation internally and preserves invariants. In C, you must manually update pointer, capacity, and terminator invariants.

## 4) Common heap bugs

Frequent bug classes:

- **Memory leak**: allocated block is never freed.
- **Use-after-free**: accessing memory after it has been freed.
- **Double free**: freeing the same block twice.
- **Returning pointer to freed memory**: caller receives dangling pointer.

These often come from unclear ownership or partial-failure cleanup paths.

### Example

```c
char* p = malloc(8);
if (!p) return;
free(p);
/* BUG: use-after-free */
p[0] = 'x';
```

### Common mistakes

- Freeing in one branch but continuing to use pointer in another.
- Not nulling pointer after free when pointer remains in scope.
- Forgetting cleanup on early returns.

> **C vs C++:** Destructors reduce accidental leaks in idiomatic C++, but raw-pointer C++ code can still have identical bugs. C simply gives fewer default safety rails.

## 5) Defensive allocation and error-path cleanup

Always check allocation results before use. Build cleanup paths that release all resources acquired so far.

A common style in C:

- initialize pointers to `NULL`
- allocate step by step
- on failure, jump to cleanup label
- free what is non-NULL

### Example

```c
bool build_two_buffers(char** out_a, char** out_b) {
    char* a = NULL;
    char* b = NULL;

    a = malloc(32);
    if (a == NULL) goto fail;

    b = malloc(64);
    if (b == NULL) goto fail;

    *out_a = a;
    *out_b = b;
    return true;

fail:
    free(b);
    free(a);
    return false;
}
```

### Common mistakes

- Ignoring `NULL` return and dereferencing immediately.
- Freeing only the most recent allocation on failure.
- Forgetting to preserve NUL termination invariant after append/grow.

> **C vs C++:** C++ exceptions and stack unwinding can automate cleanup when RAII types are used. In C, cleanup is manual and must be coded in each error path.
