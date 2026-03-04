# Day 31 Notes - Static memory pools

## 1) Why embedded systems avoid malloc

Heap allocation can cause:
- fragmentation over long uptime
- non-deterministic allocation latency
- complex failure handling paths

In real-time/safety systems, deterministic behavior is often preferred over
general-purpose flexibility.

## 2) Memory pool pattern

A pool pre-allocates:
- one backing array
- fixed block size
- fixed block count

Allocation/deallocation become pointer manipulations rather than heap syscalls.

## 3) Free-list trick

When a block is free, its first bytes can store pointer to next free block:
- `*(void**)block = next_free`

This avoids external metadata arrays and keeps overhead minimal.

## 4) Alignment and block size

Block size should be at least `sizeof(void*)` so next-pointer fits.
In practice, block size is often aligned to pointer or cache-line boundaries.

Misalignment can hurt performance or even be invalid on stricter architectures.

## 5) Operational complexity

With free-list:
- alloc: pop head (O(1))
- free: push head (O(1))

No scans needed for steady-state operations.

## Common mistakes

- Double-freeing same block (corrupts free-list chain).
- Using block size smaller than pointer size.
- Forgetting to initialize list links in `pool_init`.
- Freeing pointers not owned by pool.

## C vs C++

- C++ offers allocator abstractions (`std::pmr`), but low-level pool concepts
  remain the same.
- In C, explicit control is straightforward but requires strict invariants.
