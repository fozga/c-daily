# Day 31 Notes - Static memory pools

## 1) Why embedded systems avoid malloc

`malloc` is a general-purpose heap allocator designed for maximum flexibility,
but it comes with costs that are unacceptable in some domains:

**Fragmentation** — after many alloc/free cycles the heap may hold enough free
bytes in total, but no contiguous block large enough to satisfy the next
request.  The program crashes even though "memory is available."

**Non-deterministic latency** — the allocator must scan free-block metadata
and may coalesce adjacent free regions.  Execution time varies with heap state.
In hard real-time systems (motor controllers, pacemakers, avionics), every
function must complete within a bounded time.

**Failure handling complexity** — `malloc` can return NULL.  Every call site
must check and handle that case.  In safety-critical code this doubles the
number of branches to audit.

A static memory pool eliminates all three problems: memory is pre-allocated at
program start, and each alloc/free operation takes exactly O(1) time.

## 2) Memory pool data model

A pool owns:

- one **backing byte array** (`uint8_t buf[BLOCK_SIZE * BLOCK_COUNT]`)
- a **free-list head** pointer (starts at the first block)
- fixed `block_size` and `block_count` values

The backing array never changes size.  Only the free-list linkage changes.

## 3) The free-list trick

When a block is free, its first `sizeof(void*)` bytes are repurposed to store
a pointer to the **next** free block.  No external metadata array is needed.

```
pool.free_head
      │
      ▼
  ┌──────────┐    ┌──────────┐    ┌──────────┐
  │ next ────┼───►│ next ────┼───►│ next=NULL│  ← three free blocks
  │ (unused) │    │ (unused) │    │ (unused) │
  └──────────┘    └──────────┘    └──────────┘
```

After `pool_alloc()` pops the head:

```
pool.free_head
      │
      ▼
  ┌──────────┐    ┌──────────┐
  │ next ────┼───►│ next=NULL│
  │ (unused) │    │ (unused) │
  └──────────┘    └──────────┘
  [block returned to caller — payload area is now theirs]
```

### Example: pool_init, pool_alloc, pool_free

```c
#include <stdint.h>
#include <stddef.h>
#include <assert.h>

#define BLOCK_SIZE  64u
#define BLOCK_COUNT 16u

typedef struct Pool {
    uint8_t  buf[BLOCK_SIZE * BLOCK_COUNT];
    void    *free_head;
    size_t   block_size;
    size_t   block_count;
} Pool;

void pool_init(Pool *p) {
    p->block_size  = BLOCK_SIZE;
    p->block_count = BLOCK_COUNT;

    /* Link every block into the free list */
    for (size_t i = 0; i < BLOCK_COUNT - 1; i++) {
        void *cur  = p->buf + i * BLOCK_SIZE;
        void *next = p->buf + (i + 1) * BLOCK_SIZE;
        *(void **)cur = next;          /* first bytes = pointer to next block */
    }
    /* Last block: next = NULL */
    void *last = p->buf + (BLOCK_COUNT - 1) * BLOCK_SIZE;
    *(void **)last = NULL;

    p->free_head = p->buf;             /* head points at block 0 */
}

void *pool_alloc(Pool *p) {
    if (!p->free_head) return NULL;    /* pool exhausted */
    void *block    = p->free_head;
    p->free_head   = *(void **)block;  /* advance head to next free block */
    return block;
}

void pool_free(Pool *p, void *block) {
    /* Push block back onto the head of the free list */
    *(void **)block  = p->free_head;
    p->free_head     = block;
}
```

`pool_alloc` and `pool_free` each contain **no loops** — they are O(1)
regardless of how many blocks the pool holds.

## 4) Alignment and block size

The free-list trick stores a `void*` inside the block payload.  Therefore:

- `block_size` must be ≥ `sizeof(void*)` (8 bytes on 64-bit).

In practice, align block size to the platform's natural alignment or a cache
line (64 bytes is common) to avoid both strict-alignment traps and false
sharing.

```c
/* portable block-size alignment helper */
#define ALIGN_UP(n, a)  (((n) + (a) - 1) & ~((a) - 1))
size_t aligned_size = ALIGN_UP(requested_size, sizeof(void*));
```

## 5) Operational complexity

| Operation | Time complexity | Code complexity |
|---|---|---|
| `pool_alloc` | O(1) | pop one pointer |
| `pool_free` | O(1) | push one pointer |
| `pool_init` | O(N) | one-time setup loop |

The O(N) init cost is paid once, so steady-state is pure O(1).

## 6) Pool exhaustion and sentinel checks

When `free_head == NULL`, the pool is empty.  A correct `pool_alloc` returns
`NULL`; callers must check this like any resource allocation.

For the stretch goal: validate in `pool_free` that the returned pointer falls
within `[buf, buf + BLOCK_SIZE * BLOCK_COUNT)`.  Freeing a pointer outside
that range would corrupt the free list or cause undefined behaviour.

## Common mistakes

- **Double-free** — freeing the same block twice introduces a cycle in the
  free list.  Subsequent `pool_alloc` calls will return the same pointer twice,
  causing aliasing.
- **Block size too small** — using `block_size < sizeof(void*)` truncates the
  free-list pointer, corrupting the chain immediately after `pool_init`.
- **Forgetting to initialise links** — if `pool_init` skips linking some
  blocks, those blocks are unreachable and wasted.
- **Freeing a pointer not owned by the pool** — the pointer was never from
  this pool's buffer; writing to it corrupts arbitrary memory.
- **Using freed block contents** — the `void*` next-pointer is written into
  the block payload immediately on free; reading payload after freeing is a
  use-after-free bug.

## C vs C++

| Aspect | C (manual pool) | C++ (`std::pmr`) |
|---|---|---|
| Setup | Explicit `pool_init`, manual free-list | `std::pmr::monotonic_buffer_resource` or `pool_resource` |
| Ownership tracking | Caller responsibility | Allocator + smart pointer integration available |
| Alignment | Manual `ALIGN_UP` macro | `std::align` / allocator `alignment` parameter |
| Double-free detection | None (unless you add bounds checks) | Still undefined behaviour; AddressSanitizer catches it |

The low-level pool concept is identical in both languages.  C gives you
complete transparency and control; C++ layers ergonomic abstractions on top,
but understanding the underlying mechanics makes both uses safer.
