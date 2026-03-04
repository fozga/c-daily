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

Use unsigned integers for bit manipulation whenever possible. Right-shifting
signed values can be implementation-defined (arithmetic vs logical behavior),
and signed overflow is undefined.

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

Set bit:
- `x |= mask`

Clear bit:
- `x &= ~mask`

Toggle bit:
- `x ^= mask`

Test bit:
- `(x & mask) != 0`

These operations update one bit without disturbing other bits.

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
