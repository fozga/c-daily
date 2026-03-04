# Day 34 - Circular Ring Buffers

## Goal
Build a fast, array-backed ring buffer for streaming bytes.

## Context
UART, SPI, and network sockets all rely on circular buffers to decouple the
hardware interrupt from the main processing loop.

## Task (45-60 min)
- Review `ringbuf.h`. The struct contains a statically allocated array.
- Implement `rb_push` and `rb_pop` using head (write index) and tail
  (read index).
- Use the "always keep one slot empty" rule to distinguish between a full
  buffer and an empty buffer without needing a separate count variable.
- Run `make test`.

## Acceptance criteria
- `make test` passes (0 warnings).
- Wrapping around the end of the array works seamlessly.
- Answers to all knowledge questions provided.

## Knowledge check
There are 8 questions in `solution/README.md`.

## Stretch goals
- If capacity is a power of 2, rewrite `% capacity` as
  `& (capacity - 1)` for performance.
