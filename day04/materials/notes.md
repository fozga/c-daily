# Day 04 Notes - Arrays and Pointer Arithmetic

These notes focus on how raw memory traversal works in C and why explicit bounds discipline is mandatory.

## 1) Arrays in C: contiguous layout and `sizeof`

An array in C is a contiguous block of elements of the same type. For `int arr[10]`, memory holds 10 adjacent `int` objects.

`sizeof(arr)` gives total bytes of the entire array when `arr` is an actual array in the same scope. If `arr` has 10 `int` elements and `sizeof(int) == 4`, then `sizeof(arr)` is 40.

A pointer is different: `sizeof(ptr)` returns the size of the pointer itself (typically 8 on 64-bit), not the data it points to.

### Example

```c
int arr[10];
int* p = arr;

size_t arr_bytes = sizeof(arr);   /* 10 * sizeof(int) */
size_t ptr_bytes = sizeof(p);     /* size of pointer, not array */
```

### Common mistakes

- Assuming `sizeof(ptr)` is the size of pointed data.
- Computing element count from a pointer with `sizeof(ptr) / sizeof(ptr[0])`.
- Passing only a pointer to a function and expecting it to know array length.

> **C vs C++:** In modern C++, types like `std::array` and `std::span` can carry size information. In C, raw arrays decay and lose bound metadata unless passed explicitly.

## 2) Array-to-pointer decay

In most expressions, an array value decays to a pointer to its first element. Function parameters like `int arr[10]` are adjusted by the language to `int* arr`.

That means size information is not preserved in the parameter type. You must pass length separately.

### Example

```c
#include <stddef.h>

void f(int arr[10], size_t n) {
    (void)n;
    /* Here arr is effectively int* */
}

void g(void) {
    int xs[10] = {0};
    f(xs, 10);
}
```

### Common mistakes

- Expecting `int arr[10]` in a parameter to enforce runtime size 10.
- Using `sizeof(arr)` inside a function parameter context to get element count.
- Not passing `n` and then iterating past valid range.

> **C vs C++:** C++ references and templates can preserve array extent in some APIs. Plain C function parameters do not preserve array bounds.

## 3) Pointer arithmetic and `ptrdiff_t`

For pointer `p` of type `T*`, `p + 1` advances by `sizeof(T)` bytes. Arithmetic is in units of elements, not bytes.

Subtracting pointers to elements of the same array yields a value of type `ptrdiff_t` representing element distance.

### Example

```c
#include <stddef.h>

int xs[5] = {0, 1, 2, 3, 4};
int* p = &xs[1];
int* q = &xs[4];

ptrdiff_t dist = q - p;  /* 3 */
int v = *(p + 2);        /* xs[3] */
```

### Common mistakes

- Assuming pointer increments by one byte for all types.
- Subtracting pointers that do not refer into the same array object.
- Using pointer arithmetic without checking remaining length first.

> **C vs C++:** Semantics are similar, but C APIs expose raw pointers directly more often; safe traversal patterns must be designed by convention and tests.

## 4) Indexing vs dereference equivalence

In C, array indexing is defined through pointer arithmetic:

- `arr[i]` is exactly `*(arr + i)`
- `p[i]` is exactly `*(p + i)`

This equivalence explains both power and risk: indexing has no implicit bounds checks.

### Example

```c
int xs[3] = {10, 20, 30};
int* p = xs;

int a = xs[2];     /* 30 */
int b = *(xs + 2); /* 30 */
int c = p[1];      /* 20 */
```

### Common mistakes

- Thinking `[]` is safer than pointer arithmetic.
- Forgetting that `p[i]` requires valid memory for all `0 <= i < n`.
- Mixing signed indices with unsigned lengths without checks.

> **C vs C++:** C++ containers provide `.at()` with bounds checking in many cases. C raw pointers/arrays never check bounds for you.

## 5) Bounds discipline in C

C does not enforce array bounds at runtime. Safety depends on explicit contracts and checks:

- always pass `(pointer, length)` together
- track cursor/index carefully
- validate before read/write
- never allow cursor to exceed capacity

Off-by-one bugs are common:

- reading when `cursor == capacity`
- using `<= capacity` instead of `< capacity`
- advancing cursor before validating requested byte count

### Variable-length arrays (VLAs)

C99 introduced VLAs: arrays whose size is determined at runtime, e.g. `int buf[n]`. They allocate on the stack, so a large or attacker-controlled `n` causes a stack overflow — there is no bounds check and no `NULL` return to detect failure. The `-Wvla` warning flag signals every use of a VLA. In production-quality C code, prefer fixed-size stack arrays or explicit heap allocation instead of VLAs.

### Example

```c
#include <stddef.h>
#include <stdint.h>

int read_byte(const uint8_t* data, size_t cap, size_t* cursor, uint8_t* out) {
    if (!data || !cursor || !out) return -1;
    if (*cursor >= cap) return -1;
    *out = data[*cursor];
    *cursor += 1;
    return 0;
}
```

### Common mistakes

- Checking bounds after dereference rather than before.
- Not validating `cursor + n` against capacity before block copy.
- Assuming tests with small inputs prove bounds correctness.

> **C vs C++:** In C++, abstractions like `std::span` make size explicit and composable. In C, you must propagate and enforce length manually in every layer.
