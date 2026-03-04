# Day 29 Solution Workspace

## Build and run

- `make test` - build and run thread-safety tests.
- `make asan` - run tests with AddressSanitizer.
- `make valgrind` - run tests under Valgrind.
- `make clean` - remove generated binaries.

## Answers

**Q1: Why is `count++` not thread-safe, even on a modern x86 CPU?**  

> Your answer here...

---

**Q2: In the shared-index work-queue pattern, why is file I/O performed outside the mutex lock?**  

> Your answer here...

---

**Q3: What is returned by `thrd_create` on failure, and what two distinct failure reasons exist?**  

> Your answer here...

---

**Q4: What is the consequence of reading the final `total` before calling `thrd_join` on all workers?**  

> Your answer here...

---

**Q5: Why does a data race on a plain `int` constitute undefined behaviour in C11, not just a "possible wrong value"?**  

> Your answer here...

---

**Q6: Describe the tradeoff between using `mtx_t` and `_Atomic long` for accumulating the match total across threads.**  

> Your answer here...

---

**Q7: If you launch 8 threads over 8 files of wildly different sizes, why does the shared-index pattern outperform static range partitioning?**  

> Your answer here...

---

**Q8: A colleague removes `mtx_destroy` at cleanup, arguing "the process exits anyway." Under what realistic scenario does this cause a real bug?**  

> Your answer here...

---
