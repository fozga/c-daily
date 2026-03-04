# Day 19 Solution Workspace

## Build and run

- `make test` - build and run tests.
- `make asan` - run tests with AddressSanitizer.
- `make valgrind` - run tests under Valgrind.
- `make clean` - remove generated binaries.

## Answers

**Q1: Why is open addressing often faster than chaining for lookup-heavy workloads on modern CPUs? What hardware characteristic makes the difference?**  

> Your answer here...

---

**Q2: Why must the map call `strdup` (or equivalent) on the key string rather than storing the caller's `const char*` pointer directly? Give two distinct scenarios where storing the pointer would cause silent corruption.**  

> Your answer here...

---

**Q3: Why does resizing by `memcpy` produce an immediately broken table? Walk through a concrete two-element example showing how a previously valid probe chain becomes unreachable after the capacity changes.**  

> Your answer here...

---

**Q4: What is a tombstone, and why is it necessary when deleting entries from a linear-probing table? Show with an example how omitting tombstones causes `get` to return false-negative results.**  

> Your answer here...

---

**Q5: What does load factor measure, and why does this implementation trigger a resize at 0.75 rather than at 0.99 or 0.5?**  

> Your answer here...

---

**Q6: When a `put` operation finds that the key already exists and updates the value, what memory management steps must happen in what order to avoid a leak?**  

> Your answer here...

---

**Q7: During a resize, you transfer key strings from the old table to the new table. Should you call `strdup` again on each key, or transfer the existing heap pointer? Explain why the wrong choice causes either a double-free or a leak.**  

> Your answer here...

---

**Q8: How does the average number of probes required for a lookup grow as load factor approaches 1.0 in linear probing? Why does this become catastrophic near full capacity?**  

> Your answer here...
