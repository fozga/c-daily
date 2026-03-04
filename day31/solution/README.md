# Day 31 Solution Workspace

## Build and run

- `make test` - build and run pool tests.
- `make asan` - run tests with AddressSanitizer.
- `make valgrind` - run tests under Valgrind.
- `make clean` - remove generated binaries.

## Answers

**Q1: What is heap fragmentation and why does it cause allocation failures even when total free bytes are sufficient?**  

> Your answer here...

---

**Q2: Walk through exactly what happens to `pool.free_head` when `pool_alloc` is called on a pool containing three free blocks. What are the pointer values before and after?**  

> Your answer here...

---

**Q3: Why must `block_size` be at least `sizeof(void*)`, and what exactly goes wrong at runtime if it is smaller?**  

> Your answer here...

---

**Q4: A caller calls `pool_free` on the same pointer twice. Describe, step by step, how the free list becomes corrupted and what subsequent `pool_alloc` calls return.**  

> Your answer here...

---

**Q5: Why does `pool_init` run in O(N) while `pool_alloc` and `pool_free` are O(1)? Justify that neither alloc nor free contains a loop.**  

> Your answer here...

---

**Q6: In a safety-critical RTOS task, a developer proposes switching from `malloc` to a static pool. List three concrete properties of the pool that make this acceptable to a certifying body (e.g. DO-178C, IEC 61508).**  

> Your answer here...

---

**Q7: A developer reads the first few bytes of a block immediately after calling `pool_free` on it, arguing the memory "still belongs to the pool." Explain why this is a use-after-free bug.**  

> Your answer here...

---

**Q8: Design a lightweight sentinel check for `pool_free` that detects an out-of-range pointer. Write the condition in C and explain what it prevents.**  

> Your answer here...

---
