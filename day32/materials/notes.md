# Day 32 Notes - C11 Threads and Atomics

## C11 Atomics vs Mutexes

`<stdatomic.h>` provides atomic operations that can update shared variables
without using a lock. A mutex serializes access by blocking competing threads.

Use lock-free approaches when:
- the data path is small and highly contended
- you need low latency and minimal context-switch overhead
- you can keep the algorithm simple and provably correct

Use mutexes when:
- shared state is complex or multi-step
- correctness and maintainability are more important than micro-optimizations
- lock-free invariants would become difficult to reason about

Mutexes can trigger kernel scheduling and context switches under contention.
Atomic operations are CPU-level synchronization primitives and can be much
faster for simple coordination patterns.

## `_Atomic` syntax

C11 supports:
- `_Atomic int x;`
- `atomic_int y;` (typedef-style convenience)

For queue indexes, using `_Atomic size_t` is natural:
- producer updates `head`
- consumer updates `tail`
- each side reads the opposite index atomically

## SPSC Ring Buffer Mechanism

For a queue with `capacity = N`, store elements in `data[0..N-1]`.

Producer:
1. Read `head` and `tail`.
2. Compute `next_head = (head + 1) % N`.
3. If `next_head == tail`, queue is full.
4. Write value to `data[head]`.
5. Publish `head = next_head`.

Consumer:
1. Read `head` and `tail`.
2. If `head == tail`, queue is empty.
3. Read value from `data[tail]`.
4. Publish `tail = (tail + 1) % N`.

## Empty and Full Conditions

- Empty: `head == tail`
- Full: `(head + 1) % capacity == tail`

This design intentionally keeps one slot unused to distinguish full from empty
without adding extra counters.

## Memory Ordering Basics

Why not plain `head = new_head`?
- Compilers may reorder operations for optimization.
- CPUs may observe memory operations in different orders across cores.

Atomic operations establish the required inter-thread visibility guarantees.
For this day, default sequential consistency (`memory_order_seq_cst`) is used,
which is the strictest and easiest model to reason about.

## Common mistakes

- Advancing `head` before writing payload into `data[head]`.
- Reading from `data[tail]` before confirming queue is non-empty.
- Using non-atomic shared indexes in multithreaded code.
- Forgetting modulo wrap-around when incrementing indexes.
- Using multi-producer or multi-consumer patterns with this SPSC design.

## C vs C++ callout

C++ offers `std::atomic<T>` and higher-level concurrency utilities, but the
core memory-order reasoning is the same. In C, the primitives are explicit in
`<stdatomic.h>`, which helps build a clear mental model of synchronization.
