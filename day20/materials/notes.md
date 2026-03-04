# Day 20 Notes - Dynamic bitsets in C

## 1) Bitwise operators overview

Core operators:
- `&` (AND)
- `|` (OR)
- `^` (XOR)
- `~` (bitwise NOT)

These operate on bits directly, unlike logical operators (`&&`, `||`) which
evaluate truthiness and short-circuit.

## 2) Bit shifts and signedness

Shift operators:
- `<<` left shift
- `>>` right shift

Use unsigned integers for bit manipulation whenever possible:

- **Right-shifting a signed integer** may produce either arithmetic (sign-bit
  fill) or logical (zero-fill) behavior — the C standard says the result is
  implementation-defined when the value is negative.
- **Left-shifting into or past the sign bit** of a signed integer is
  undefined behavior (UB) — the compiler is free to produce any result.
- **Signed integer overflow** is also undefined behavior (UB) — unlike
  unsigned overflow, which wraps modulo 2ⁿ.

Declaring bit-manipulation variables as `uint32_t` or `uint64_t` eliminates
all three hazards at once.

## 3) Bit mask pattern

To target one bit:
- `mask = (1ULL << bit_index)`

Use `1ULL`, not plain `1`, so the constant is 64-bit unsigned. Otherwise
expressions like `1 << 40` may overflow/truncate on 32-bit int type.

## 4) Indexing a bitset array

Given global bit index `bit`:

- `block_index = bit / 64`
- `bit_offset = bit % 64`

Then access:
- `blocks[block_index]`

with a mask at `bit_offset`.

## 5) Operations with masks

### Example — all four operations in context

```c
#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include <assert.h>

#define BITS_PER_BLOCK  64

typedef struct {
    uint64_t *blocks;
    size_t    num_bits;
    size_t    num_blocks;
} bitset_t;

static inline size_t block_index(size_t bit) { return bit / BITS_PER_BLOCK; }
static inline size_t bit_offset (size_t bit) { return bit % BITS_PER_BLOCK; }

void bitset_set(bitset_t *bs, size_t bit) {
    assert(bit < bs->num_bits);
    bs->blocks[block_index(bit)] |= (1ULL << bit_offset(bit));   /* OR: set */
}

void bitset_clear(bitset_t *bs, size_t bit) {
    assert(bit < bs->num_bits);
    bs->blocks[block_index(bit)] &= ~(1ULL << bit_offset(bit));  /* AND NOT: clear */
}

void bitset_toggle(bitset_t *bs, size_t bit) {
    assert(bit < bs->num_bits);
    bs->blocks[block_index(bit)] ^= (1ULL << bit_offset(bit));   /* XOR: flip */
}

bool bitset_test(const bitset_t *bs, size_t bit) {
    assert(bit < bs->num_bits);
    return (bs->blocks[block_index(bit)] & (1ULL << bit_offset(bit))) != 0;
}
```

Key points:
- `1ULL` ensures the shift operand is a 64-bit unsigned value; `1 << 63`
  would be undefined behavior (UB) on a platform where `int` is 32 bits.
- Each operation touches exactly one bit and leaves all others unchanged.
- `assert` enforces bounds before any pointer arithmetic, turning an out-of-
  bounds access (which would be UB) into a clean, diagnosable abort.

## Common mistakes

- Using `1 << n` instead of `1ULL << n` for high bit positions.
- Forgetting bounds checks before bit access.
- Mixing signed and unsigned shifts.
- Miscomputing `block_index`/`bit_offset`.
- Assuming `bool` array memory footprint is as compact as bitset.

## C vs C++

- C++ offers `std::bitset<N>` (fixed size) and specialized `vector<bool>`.
- In C, dynamic bitsets are implemented manually with arrays and masks.
- C gives low-level control, but correctness relies on strict index and type
  discipline.
