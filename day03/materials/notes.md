# Day 03 Notes - Pointers, Objects, and Lifetime

These notes connect C pointer mechanics to a C++ mental model, with emphasis on lifetime and aliasing rules that often cause subtle bugs.

## 1) C pointers vs C++ references

In C, pointers are ordinary values holding addresses. They can be null, copied, compared, and re-assigned to point somewhere else. Dereferencing is explicit (`*p`).

C++ references differ: they are not nullable in normal usage, must be bound at initialization, and cannot be reseated. C has no reference syntax in the language core, so pointer contracts must be explicit in API docs.

### Example

```c
#include <stdio.h>

int main(void) {
    int x = 10;
    int y = 20;

    int* p = &x;
    printf("%d\n", *p); /* 10 */

    p = &y;              /* reseat pointer */
    printf("%d\n", *p); /* 20 */

    p = NULL;            /* valid pointer state in C */
    return 0;
}
```

### Common mistakes

- Treating a pointer like a guaranteed-valid reference.
- Forgetting that pointer reseating changes alias relationships.
- Dereferencing without checking the API preconditions.

> **C vs C++:** C pointers are explicit, nullable address values. C++ references model aliasing with stronger binding guarantees and different syntax/semantics.

## 2) Storage duration and object lifetime

C objects can have different storage durations:

- **Automatic (stack-like):** local variables inside a block/function; lifetime ends at block exit.
- **Static:** global variables and `static` locals; lifetime is entire program.
- **Allocated (heap):** created via allocation functions (`malloc`/`calloc`/`realloc`); lifetime until explicitly released with `free`.
- **Thread (C11):** objects declared `_Thread_local`; lifetime spans one thread. Rarely needed at this level but worth knowing exists.

A pointer is only valid while the pointed object is alive. A pointer that outlives its pointee is called a **dangling pointer**. Accessing memory through a dangling pointer is undefined behavior (UB); the program may crash, silently read stale data, or appear to work depending on stack state.

Returning a pointer to a local automatic variable is a classic dangling-pointer mistake: that object dies when the function returns.

### Example

```c
int* bad_ptr(void) {
    int local = 42;
    return &local; /* UB: local lifetime ends on return */
}
```

```c
int* good_ptr_static(void) {
    static int value = 42;
    return &value; /* valid while program runs */
}
```

### Common mistakes

- Returning addresses of locals.
- Keeping pointers to stack objects beyond their scope.
- Confusing pointer lifetime with pointee lifetime.

> **C vs C++:** C++ may hide lifetime complexity behind constructors/destructors and RAII wrappers. In C, lifetime ownership is manual and must be documented per API.

## 3) Pointer aliasing and `restrict`

Aliasing means two pointers may refer to overlapping memory. If the compiler must assume aliasing, optimization opportunities shrink.

`restrict` (C99) is a promise to the compiler: for the lifetime of that restricted pointer, the object it points to is accessed only through that pointer (and pointers derived from it). Violating this promise is undefined behavior — the compiler may generate incorrect code that silently produces wrong results, because it assumed non-aliasing for optimization purposes.

This is useful for functions like copy/transform where source and destination must not overlap. The standard library's `memcpy` is declared with `restrict` parameters for exactly this reason; `memmove` is not, and is safe for overlapping regions.

### Example

```c
void add_arrays(const int* restrict a,
                const int* restrict b,
                int* restrict out,
                size_t n) {
    for (size_t i = 0; i < n; ++i) {
        out[i] = a[i] + b[i];
    }
}
```

### Common mistakes

- Adding `restrict` without ensuring no overlap at call sites.
- Confusing `restrict` with `const` (they solve different problems).
- Assuming `restrict` is required; it is an optimization contract, not a correctness requirement in every API.

> **C vs C++:** `restrict` is a C keyword (via C99); standard C++ has no equivalent core keyword with identical semantics.

## 4) Pointer arithmetic basics

Pointer arithmetic scales by the pointed type size. Incrementing `int* p` moves by `sizeof(int)`, not one byte. Subtracting two pointers into the same array gives element distance (`ptrdiff_t`).

Never perform pointer arithmetic outside one array object (except one-past-the-end pointer formation). Dereferencing outside bounds is undefined behavior.

### Example

```c
#include <stddef.h>

int arr[] = {10, 20, 30, 40};
int* p = &arr[0];
int* q = p + 2;     /* points to arr[2] */
ptrdiff_t d = q - p; /* d == 2 */
```

### Common mistakes

- Assuming pointer increments are byte-by-byte for all types.
- Doing arithmetic across unrelated objects.
- Forming one-past pointers and then dereferencing them.

> **C vs C++:** Arithmetic semantics are very similar, but C APIs rely on raw pointers more often than C++ codebases using iterators/containers.

## 5) Defensive pointer practices

Defensive code turns pointer assumptions into explicit checks and const-correct signatures.

- Validate pointers before dereference when function contracts permit null input.
- Keep read-only data as `const`.
- Understand declaration meaning:
  - `const int* p` -> pointer to const int (p can move, value through p is read-only)
  - `int* const p` -> const pointer to int (p fixed, pointed value mutable)

### Example

```c
int sum_first_two(const int* xs, int* out) {
    if (xs == NULL || out == NULL) {
        return -1;
    }
    *out = xs[0] + xs[1];
    return 0;
}
```

### Common mistakes

- Missing null checks on error-returning APIs.
- Using non-const pointer params for read-only inputs.
- Misreading `const` placement and mutating wrong side.

> **C vs C++:** C has fewer type-system guardrails and no references to express non-null intent; const-correctness and explicit contracts carry more of the safety burden.
