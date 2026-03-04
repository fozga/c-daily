# Day 08 Solution Workspace

## Build and run

- `make test` - build and run tests.
- `make asan` - run tests with AddressSanitizer.
- `make valgrind` - run tests under Valgrind.
- `make clean` - remove generated binaries.

## Answers

**Q1: Why does `qsort` accept `const void*` comparator arguments instead of typed pointers, and what responsibility does that place on the comparator author?**  

> Your answer here...

---

**Q2: A comparator is written as `return *(int*)a - *(int*)b`. Under what inputs does this produce wrong results, and why is signed overflow the root cause?**  

> Your answer here...

---

**Q3: What is the algorithmic consequence of calling `bsearch` on an array that was never sorted, and why can it silently return wrong results rather than always returning NULL?**  

> Your answer here...

---

**Q4: How would you implement a comparator that sorts an array of structs first by a string field, then breaks ties by a numeric field?**  

> Your answer here...

---

**Q5: Why is `qsort` not guaranteed to be stable, and in what real-world scenario would instability visibly corrupt a multi-pass sorting strategy?**  

> Your answer here...

---

**Q6: List the three mathematical properties a valid total-order comparator must satisfy. For each one, describe a concrete bug that arises when it is violated.**  

> Your answer here...

---

**Q7: After calling `qsort` to sort records by `id`, you then call `qsort` again to sort by `name`. Is it now safe to call `bsearch` with the `cmp_by_id` comparator? Explain why or why not.**  

> Your answer here...

---

**Q8: How would you store a comparator function pointer inside a struct so that different instances of a "sorter" object can use different orderings at runtime?**  

> Your answer here...

---
