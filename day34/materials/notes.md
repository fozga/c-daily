# Day 34 Notes - Circular Ring Buffers

## Ring buffer mechanics

A ring buffer stores a stream in a fixed-size array with two moving indexes:
- `head`: where the next write goes
- `tail`: where the next read comes from

Neither operation shifts array contents. This avoids O(n) movement and keeps
push/pop operations O(1).

## Wrap-around with modulo arithmetic

When an index reaches the end of the array, it wraps:

`next_index = (current + 1) % capacity`

This gives the circular behavior over linear memory.

## The full-vs-empty ambiguity

If `head == tail` means empty, how do we represent full? There are two common
solutions:

1. Keep an explicit `count` variable.
2. Keep one slot always empty.

For this day we use the empty-slot pattern:
- Empty: `head == tail`
- Full: `(head + 1) % capacity == tail`

With capacity `N`, usable payload capacity is `N - 1`.

## Why this pattern is useful

The one-empty-slot rule avoids an extra mutable counter and keeps state small.
It is common in low-level systems where simplicity and determinism matter.

## Power-of-two optimization

If `capacity` is a power of two, modulo can be replaced by a bitmask:

`next = (current + 1) & (capacity - 1)`

Example:
- `x % 256` is equivalent to `x & 255`.

Many embedded developers exploit this for predictable and fast index updates.

## Common mistakes

- Overwriting unread data by pushing into a full buffer.
- Popping from an empty buffer and reading uninitialized bytes.
- Forgetting wrap-around on head/tail updates.
- Using inconsistent full/empty definitions across functions.
- Assuming useful capacity is `N` instead of `N - 1` with empty-slot pattern.

## C vs C++ callout

C++ often wraps this logic in container classes or templates. In C, a plain
`struct` with explicit functions keeps behavior transparent and easy to audit,
which is often preferred in firmware and systems code.
