# Day 34 Notes - Circular Ring Buffers

## 1) Why ring buffers exist

Hardware peripherals produce or consume data at rates independent of the main
program loop.  A UART interrupt fires when a byte arrives; the main loop may
not be ready to process it immediately.  A ring buffer decouples the two:

- the **producer** (ISR / DMA / network layer) writes when data is ready
- the **consumer** (main loop / protocol parser) reads when it has time

Without a ring buffer, either the producer must block (impossible in an ISR)
or data is lost.

The ring buffer achieves O(1) push and pop with no dynamic allocation and no
data movement — only two index variables move.

## 2) Data structure

```c
#define RB_CAPACITY 16   /* usable slots = RB_CAPACITY - 1 */

typedef struct {
    uint8_t buf[RB_CAPACITY];
    size_t  head;   /* write index: next byte goes here       */
    size_t  tail;   /* read  index: next byte comes from here */
} RingBuf;
```

`head` and `tail` start at 0 and never decrease — they are advanced modulo
`RB_CAPACITY`.

## 3) Empty and full conditions with the one-empty-slot rule

If both `head == tail` means "empty" and also "full", we cannot distinguish
the two states without extra information.

Two solutions:

| Solution | Tradeoff |
|---|---|
| Keep a separate `count` variable | O(1) but adds mutable state to synchronise |
| Keep one slot always empty | O(1), no extra state, minimal code |

For this day we use the **one-empty-slot** rule:

- **Empty**: `head == tail`
- **Full**: `(head + 1) % RB_CAPACITY == tail`

With capacity N, only N − 1 bytes can be live at any time.

## 4) Push and pop implementation

### Example: rb_push and rb_pop

```c
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

#define RB_CAPACITY 16

typedef struct {
    uint8_t buf[RB_CAPACITY];
    size_t  head;
    size_t  tail;
} RingBuf;

void rb_init(RingBuf *rb) {
    rb->head = 0;
    rb->tail = 0;
}

bool rb_full(const RingBuf *rb) {
    return (rb->head + 1) % RB_CAPACITY == rb->tail;
}

bool rb_empty(const RingBuf *rb) {
    return rb->head == rb->tail;
}

bool rb_push(RingBuf *rb, uint8_t byte) {
    if (rb_full(rb)) return false;       /* reject when full — never overwrite */
    rb->buf[rb->head] = byte;
    rb->head = (rb->head + 1) % RB_CAPACITY;
    return true;
}

bool rb_pop(RingBuf *rb, uint8_t *out) {
    if (rb_empty(rb)) return false;      /* nothing to read */
    *out = rb->buf[rb->tail];
    rb->tail = (rb->tail + 1) % RB_CAPACITY;
    return true;
}
```

Neither function loops or allocates — both are O(1).

## 5) Wrap-around with modulo arithmetic

`head` and `tail` advance as:

```c
head = (head + 1) % RB_CAPACITY;
```

When `head` reaches `RB_CAPACITY - 1` and is incremented, modulo wraps it to
0, reusing the beginning of the array.  The logical stream is unbounded; the
physical storage is fixed and circular.

A common trace:

```
Initial:  head=0, tail=0          (empty)
Push 'A': buf[0]='A', head=1
Push 'B': buf[1]='B', head=2
Pop:      out='A', tail=1
Push 'C': buf[2]='C', head=3
Pop:      out='B', tail=2
Pop:      out='C', tail=3         (empty again: head==tail)
```

## 6) Power-of-two optimisation (stretch goal)

When `RB_CAPACITY` is a power of two, modulo is equivalent to a bitmask:

```c
/* General (any capacity): */
head = (head + 1) % RB_CAPACITY;

/* Optimised (power-of-two capacity only): */
head = (head + 1) & (RB_CAPACITY - 1);
```

Examples: `% 8` ≡ `& 7`, `% 256` ≡ `& 255`.  The bitwise AND version
compiles to a single instruction on every architecture and avoids a division
(or compiler-inserted multiply-and-shift sequence) in the hot path.

## 7) Thread safety

The `rb_push` / `rb_pop` functions above are **not thread-safe** as written.
In a multithreaded context you need either:

- a mutex wrapping each push/pop call, or
- an SPSC design using `_Atomic` indexes (see Day 32)

For bare-metal ISR use, disabling the interrupt during the push (or using the
Day 32 atomic approach) prevents the race between the ISR and the main loop.

## Common mistakes

- Pushing into a full buffer without checking — silently overwrites unread
  data and corrupts the stream.
- Popping from an empty buffer — returns stale bytes and advances `tail` past
  live data.
- Forgetting the modulo wrap — `head` or `tail` runs off the end of the array
  (undefined behaviour on the next access).
- Using inconsistent full/empty definitions across `rb_push` and `rb_pop` (one
  uses `>= capacity`, the other uses `== capacity - 1`).
- Assuming usable capacity is N instead of N − 1 when sizing the buffer.

## C vs C++ callout

| Aspect | C (manual ring buffer) | C++ equivalent |
|---|---|---|
| Data structure | Plain `struct` + two `size_t` | `std::queue`, `boost::circular_buffer`, or custom |
| Error handling | Return `bool`; caller checks | Throw exception or use `std::optional<T>` |
| Generality | Fixed type; manual instantiation | Template `RingBuf<T, N>` |
| ISR safety | Direct; no hidden allocations | Same if template avoids dynamic allocation |

In C, the transparency of the ring buffer struct is a feature in firmware
contexts: you can inspect head/tail in a debugger, in a register, or via a
JTAG probe without source-level tooling support.
