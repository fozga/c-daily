# Day 32 Solution Workspace

## Build and run

From this directory:

```bash
make test
make asan
make valgrind
make clean
```

## Answers

**Q1: Why must the producer write `data[head]` before calling `atomic_store(&q->head, next)`? What does the consumer observe if the order is reversed?**  

> Your answer here...

---

**Q2: The SPSC queue is safe without a mutex because each index is owned by exactly one thread. Explain precisely what breaks if a second producer thread calls `sq_push` concurrently.**  

> Your answer here...

---

**Q3: `atomic_store` with default `memory_order_seq_cst` is used instead of a plain assignment. Name two distinct sources of reordering it prevents (one compiler, one CPU).**  

> Your answer here...

---

**Q4: With `CAPACITY = 8`, trace the values of `head` and `tail` through a sequence of: push A, push B, pop, push C, pop, pop. What is the final state?**  

> Your answer here...

---

**Q5: A stretch-goal upgrade replaces `memory_order_seq_cst` with `memory_order_release` on stores and `memory_order_acquire` on loads. Why is this sufficient for SPSC correctness, and what does it gain on ARM hardware?**  

> Your answer here...

---

**Q6: If `head` and `tail` are declared as plain `size_t` instead of `_Atomic size_t`, what specific undefined behaviour clause of C11 applies, and what can the compiler legally do?**  

> Your answer here...

---

**Q7: Compare the uncontended latency of an `atomic_fetch_add` vs acquiring a `mtx_t`. When is the atomic version *slower* in practice?**  

> Your answer here...

---

**Q8: A developer changes `CAPACITY` to 1 to save memory. Without looking at the code, predict what will always happen on the first `sq_push` call. Explain the invariant that causes this.**  

> Your answer here...

---
