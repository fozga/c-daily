# Day 32 Notes - C11 Threads and Atomics (SPSC Queue)

## 1) Atomics vs mutexes

`<stdatomic.h>` provides operations that the CPU executes atomically — no
other thread can observe a half-completed state.  A mutex achieves the same
*logical* exclusion, but by blocking competing threads at the OS scheduler
level.

| Property | Atomic operation | Mutex |
|---|---|---|
| Blocking | No (spin or single instruction) | Yes (OS context switch under contention) |
| Latency (uncontended) | ~1 ns (single CPU instruction) | ~20-100 ns (syscall overhead) |
| Latency (contended) | Spin loop (wastes CPU) | OS-managed sleep (yields CPU) |
| Suitable state size | One scalar | Arbitrary struct / multi-step update |
| Correctness risk | Memory ordering bugs are subtle | Easier to reason about |

Use atomics when:

- the shared state is a single scalar (index, counter, flag)
- latency is critical
- the algorithm can be proved correct in terms of memory ordering

Use mutexes when:

- shared state involves multiple variables that must change together
- correctness is more important than micro-optimisation
- you cannot afford to reason about relaxed memory orders

## 2) `_Atomic` syntax and standard operations

C11 supports two equivalent syntaxes:

```c
_Atomic size_t head;      /* keyword style    */
atomic_size_t  tail;      /* typedef style    */
```

Standard operations:

```c
size_t h = atomic_load(&head);          /* acquire a consistent snapshot */
atomic_store(&tail, new_tail);          /* publish a new value           */
size_t old = atomic_fetch_add(&head, 1); /* read-modify-write, returns old */
```

By default these use `memory_order_seq_cst` (sequential consistency) — the
strongest and safest ordering model.

## 3) SPSC ring buffer: data structure

A Single-Producer Single-Consumer (SPSC) queue needs no mutex because exactly
one thread owns each index: the **producer** owns `head`, the **consumer**
owns `tail`.

```c
#define CAPACITY 16  /* must be > 1; usable slots = CAPACITY - 1 */

typedef struct {
    int           data[CAPACITY];
    _Atomic size_t head;   /* written only by producer */
    _Atomic size_t tail;   /* written only by consumer */
} SpscQueue;
```

The one-empty-slot rule:

- **Empty**: `head == tail`
- **Full**: `(head + 1) % CAPACITY == tail`

With capacity N, the maximum number of live items is N − 1.

## 4) Producer and consumer operations

### Example: sq_push and sq_pop

```c
#include <stdatomic.h>
#include <stdbool.h>

bool sq_push(SpscQueue *q, int value) {
    size_t h    = atomic_load(&q->head);
    size_t next = (h + 1) % CAPACITY;

    if (next == atomic_load(&q->tail))
        return false;   /* full — caller must retry or discard */

    q->data[h] = value;                /* write payload BEFORE advancing head */
    atomic_store(&q->head, next);      /* publish new head to consumer */
    return true;
}

bool sq_pop(SpscQueue *q, int *out) {
    size_t t = atomic_load(&q->tail);

    if (atomic_load(&q->head) == t)
        return false;   /* empty */

    *out = q->data[t];                     /* read payload BEFORE advancing tail */
    atomic_store(&q->tail, (t + 1) % CAPACITY);
    return true;
}
```

**Critical ordering rule**: the producer must write `data[h]` *before*
updating `head`.  If it advanced `head` first, the consumer could observe the
new head value and read uninitialised or stale data.

## 5) Memory ordering: why plain assignments are unsafe

On modern CPUs and with compiler optimisations enabled, memory operations can
be reordered:

- The compiler may move a `head = next` assignment before `data[h] = value`
  if it sees no data dependency between them.
- CPUs (non-x86 architectures) have weakly-ordered memory models and may
  commit writes to caches in a different order than the program source.

`atomic_store` with the default `memory_order_seq_cst` prevents both forms of
reordering.  For the stretch goal, `memory_order_release` on stores and
`memory_order_acquire` on loads are sufficient for SPSC — they are faster on
ARM/POWER while still providing the required visibility guarantee.

## 6) Why this is SPSC only

The algorithm relies on each index being modified by exactly one thread:

- Producer reads and writes `head`.
- Consumer reads and writes `tail`.
- Each also *reads* the other's index to detect full/empty — but never
  *writes* it.

If two producers both attempted to call `sq_push` concurrently, they would
race on the `head` read-modify-write and could both claim the same slot, then
overwrite each other's data.  This design is **not** safe for MPMC use without
additional synchronisation.

## Common mistakes

- Advancing `head` before writing `data[head]` (consumer reads garbage).
- Reading from `data[tail]` before confirming the queue is non-empty.
- Using plain (non-atomic) `size_t` for `head`/`tail` in a multithreaded
  binary — this is a data race and undefined behaviour.
- Forgetting the modulo wrap-around when incrementing indexes.
- Using this SPSC design with multiple producers or multiple consumers.
- Over-optimising to relaxed memory orders before verifying correctness
  under sequential consistency first.

## C vs C++ callout

| Aspect | C (`<stdatomic.h>`) | C++ (`<atomic>`) |
|---|---|---|
| Type | `_Atomic T` / `atomic_int` | `std::atomic<T>` |
| Load/store | `atomic_load` / `atomic_store` | `.load()` / `.store()` |
| Fetch-add | `atomic_fetch_add` | `.fetch_add()` |
| Explicit ordering | `atomic_load_explicit(..., order)` | `.load(order)` |

The underlying CPU instructions and memory-ordering semantics are identical.
C++ provides a cleaner class-based interface, but C's explicit function-call
style makes the memory-ordering intent more visible — which is a real
advantage when learning these concepts.
