# Day 12 Notes - Struct layout, padding, and binary safety

## 1) Alignment rules

CPUs and ABIs prefer aligned memory access for performance and, on some
architectures, correctness.

Typical (platform-dependent) alignments:
- `uint8_t`: 1-byte alignment
- `uint16_t`: 2-byte alignment
- `uint32_t`: 4-byte alignment
- `uint64_t`: 8-byte alignment

Compilers insert padding bytes so fields meet alignment constraints.

## 2) Padding in structs

Padding appears in two places:
- **Internal padding**: between fields
- **Tail padding**: after last field to align array elements of that struct

Padding bytes are not part of your logical data model but do affect:
- `sizeof(struct)`
- raw binary dumps via `fwrite(&s, sizeof s, 1, fp)`

This is a major source of binary format bugs.

## 3) `offsetof` for layout diagnostics

`offsetof(type, field)` reports byte offset of a field in a struct.

Use it to print and verify:
- where each field actually starts
- whether gaps/padding exist unexpectedly

Combined with `sizeof`, it gives a concrete view of memory layout.

### Example

```c
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>

/* Poorly ordered: compiler will insert 3 bytes of padding after 'flags' */
typedef struct {
    uint8_t  flags;     /* offset 0, size 1                              */
    /* 3 bytes padding inserted here to align 'id' to 4-byte boundary   */
    uint32_t id;        /* offset 4, size 4                              */
    uint16_t score;     /* offset 8, size 2                              */
    /* 2 bytes tail padding to keep array stride aligned to 4 bytes     */
} record_bad_t;         /* sizeof == 12, but only 7 bytes are your data  */

/* Well ordered: widest fields first — no internal padding needed        */
typedef struct {
    uint32_t id;        /* offset 0, size 4  */
    uint16_t score;     /* offset 4, size 2  */
    uint8_t  flags;     /* offset 6, size 1  */
    /* 1 byte tail padding (struct align == 4) */
} record_good_t;        /* sizeof == 8                                   */

void print_layout(void) {
    printf("record_bad_t:  sizeof=%zu\n", sizeof(record_bad_t));
    printf("  flags  @ offset %zu\n", offsetof(record_bad_t, flags));
    printf("  id     @ offset %zu\n", offsetof(record_bad_t, id));
    printf("  score  @ offset %zu\n", offsetof(record_bad_t, score));

    printf("record_good_t: sizeof=%zu\n", sizeof(record_good_t));
    printf("  id     @ offset %zu\n", offsetof(record_good_t, id));
    printf("  score  @ offset %zu\n", offsetof(record_good_t, score));
    printf("  flags  @ offset %zu\n", offsetof(record_good_t, flags));
}
```

## 4) Reordering fields to minimize padding

A common strategy:
- place widest-alignment fields first
- place narrow fields later

This often reduces internal padding and can make layout more compact and
predictable.

Even with reordering, never assume cross-compiler binary compatibility unless
the format is explicitly specified field-by-field.

## 5) `__attribute__((packed))` pitfalls

`packed` removes or reduces padding, but it has risks:
- unaligned accesses may be slower
- on some targets, unaligned access may trap
- can introduce undefined behavior if code assumes aligned pointers

Use packed structs only when absolutely necessary and with careful boundary
handling.

## 6) `_Static_assert` layout checks

Compile-time assertions can enforce layout invariants:
- expected struct size
- expected offsets

This catches accidental regressions early in CI/builds.

```c
/* Enforce the layout contract so any accidental struct change fails the build */
_Static_assert(sizeof(record_good_t) == 8,  "record_good_t: size changed");
_Static_assert(offsetof(record_good_t, id)    == 0, "id must be at byte 0");
_Static_assert(offsetof(record_good_t, score) == 4, "score must be at byte 4");
_Static_assert(offsetof(record_good_t, flags) == 6, "flags must be at byte 6");
```

Place these assertions in the `.c` file alongside the struct definition so they
fire as soon as the layout is touched.

## Common mistakes

- Writing structs directly to disk without defining a portable binary format.
- Assuming no padding between mixed-width fields.
- Using plain `int` in serialized structs.
- Ignoring `offsetof` diagnostics.
- Relying on `packed` everywhere instead of proper serialization.
- Not validating file size/structure before reading.

## C vs C++

- Both languages share ABI/layout sensitivity at binary boundaries.
- C++ adds extra layout complexity (vptr, non-standard-layout types).
- In both C and C++, explicit serialization is safer than raw struct dumps for
  portable formats.
