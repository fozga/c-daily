# Day 02 Notes - Integer Model and UB Traps

This note is designed for a developer who already knows C++ but needs solid C instincts around integer behavior, conversions, and undefined behavior (UB). Day 02 is about debugging numeric code that compiles but is semantically wrong at boundaries.

## 1) Integer types in practice

C integer widths are implementation-defined within standard constraints. Do not assume `int` is always 32-bit or `long` is always 64-bit. On common Linux x86_64 systems, `int` is 32-bit and `long` is 64-bit, but portability means verifying assumptions.

Use fixed-width types (`int32_t`, `uint64_t`) for file formats, protocol boundaries, and exact-range logic. Use natural types (`size_t`, `ptrdiff_t`, `int`) when operating in the host ABI/domain.

### Example

```c
#include <stdint.h>
#include <stdio.h>

int main(void) {
    printf("sizeof(int)=%zu\n", sizeof(int));
    printf("sizeof(long)=%zu\n", sizeof(long));
    printf("sizeof(long long)=%zu\n", sizeof(long long));
    printf("sizeof(int32_t)=%zu\n", sizeof(int32_t));
    return 0;
}
```

### Common mistakes

- Assuming `long` has the same width on every platform.
- Using plain `int` for serialized on-disk/network fields.
- Mixing ABI-sized types and fixed-width types without explicit conversion boundaries.

## 2) Integer promotions + usual arithmetic conversions

Before arithmetic, smaller integer types are promoted (typically to `int` or `unsigned int`). Then, for mixed operands, the usual arithmetic conversions select a common type. This can silently change signedness and value interpretation.

Typical gotcha: combining signed and unsigned values can convert the signed operand to unsigned, turning negative values into large positive values.

### Example

```c
#include <stdio.h>

int main(void) {
    int a = -1;
    unsigned int b = 1u;

    if (a < b) {
        puts("a < b");
    } else {
        puts("a >= b");
    }
    return 0;
}
```

On many platforms this prints `a >= b` because `a` is converted to an unsigned value.

### Common mistakes

- Expecting signed comparisons to stay signed in mixed expressions.
- Assuming `uint8_t` arithmetic stays 8-bit.
- Ignoring signedness diagnostics and trusting visual intuition.

## 3) Signed overflow is UB; unsigned wraparound is defined

In C, signed integer overflow is undefined behavior. The compiler may optimize assuming it never happens. Unsigned arithmetic wraps modulo 2^N by definition.

This distinction matters because “it wrapped on my machine” does not make signed overflow valid or portable.

### Example

```c
#include <stdint.h>
#include <limits.h>

int32_t bad_add(int32_t a, int32_t b) {
    /* UB when overflow occurs */
    return a + b;
}

uint32_t wrapped_add(uint32_t a, uint32_t b) {
    /* Defined modulo 2^32 */
    return a + b;
}
```

### Common mistakes

- Detecting signed overflow by first doing overflowing signed arithmetic.
- Assuming optimizer preserves overflow-check logic built on UB expressions.
- Treating signed and unsigned overflow semantics as interchangeable.

## 4) `size_t` and signed/unsigned hazards

`size_t` is an unsigned type used for sizes and indices. Hazards appear when it is mixed with signed integers:

- negative signed values can become huge after conversion to `size_t`
- subtraction on unsigned values underflows instead of becoming negative
- countdown loops can run forever if written incorrectly

### Example

```c
#include <stddef.h>
#include <stdio.h>

void bad_loop(size_t n) {
    for (size_t i = n - 1; i >= 0; --i) { /* bug: i >= 0 always true for unsigned */
        printf("%zu\n", i);
        if (i == 0) break; /* manual stop to avoid infinite loop */
    }
}
```

### Common mistakes

- Writing `for (size_t i = n - 1; i >= 0; --i)` without special handling.
- Comparing `int i` directly with `size_t n` in loop conditions.
- Assuming `a - b` with unsigned operands can express negative results.

## 5) Defensive patterns for numeric code

Use explicit boundaries and checks before operations/casts. Defensive numeric code is mostly about making invariants visible.

Recommended patterns:

- **Range checks before casts**: verify source value fits destination type.
- **Avoid unsigned subtraction when negative result is possible**: compare first, or use signed wide type.
- **Use explicit widths at boundaries**: parse into wide type, validate range, then cast.

### Example

```c
#include <stdint.h>
#include <limits.h>

int safe_to_i32(int64_t x, int32_t* out) {
    if (!out) return 1;
    if (x < INT32_MIN || x > INT32_MAX) return 2;
    *out = (int32_t)x;
    return 0;
}
```

### Common mistakes

- Casting first and checking later.
- Using “temporary unsigned arithmetic” when negative values are valid.
- Letting conversion points spread across code instead of centralizing them.

## 6) Reading compiler warnings as a debugging tool

Warnings are early bug reports from the compiler. For Day 02, expect warnings around conversions and signedness interactions.

Useful examples you may see:

1. `conversion from 'size_t' to 'int32_t' may change value`  
   Meaning: narrowing conversion can lose information.
2. `comparison of integer expressions of different signedness`  
   Meaning: implicit conversion may change comparison semantics.
3. `conversion to 'uint32_t' from 'int' may change the sign of the result`  
   Meaning: negative signed values may become large unsigned values.

### Example

```bash
gcc -std=c11 -O0 -g -Wall -Wextra -Wpedantic -Werror -Wconversion -Wsign-conversion tests.c buggy_numeric.c -o test_runner
```

### Common mistakes

- Silencing warnings without understanding the data-flow bug.
- Disabling strict warnings because they are "too noisy".
- Fixing warning text mechanically instead of fixing the semantic root cause.

## 7) Debugging workflow for Day 02

Use a repeatable loop:

1. **Reproduce**: run `make test` and capture exact failing output.
2. **Minimize**: isolate one failing case with smallest input.
3. **Hypothesize**: identify which conversion/overflow rule is involved.
4. **Patch**: apply minimal targeted fix in `buggy_numeric.c`.
5. **Test**: rerun all tests and add regression tests for the case.
6. **Sanitize**: run `make asan` and `make valgrind`.

### Example

```bash
make clean
make test
make asan
make valgrind
```

### Common mistakes

- Changing too many lines at once, then losing causal clarity.
- Declaring success after one fixed test without regression coverage.
- Skipping sanitizer passes after logic changes.

Do not guess numeric behavior. Make conversions explicit, validate ranges, and let warnings guide you.
