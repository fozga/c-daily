# Day 17 Solution Workspace

## Build and run

- `make test` - run functional tests (expected to pass despite leaks).
- `make asan` - run AddressSanitizer checks.
- `make valgrind` - run leak analysis with Memcheck.
- `make clean` - remove generated binaries.

## Answers

**Q1: What is the difference between "definitely lost" and "still reachable" in Valgrind's leak categories, and which one is always a bug that must be fixed?**  

> Your answer here...

---

**Q2: Why does fixing a "definitely lost" leak often automatically eliminate "indirectly lost" bytes in the same Valgrind run?**  

> Your answer here...

---

**Q3: What does `--track-origins=yes` add to a Valgrind run, and why is it essential for diagnosing "Conditional jump depends on uninitialised value" errors?**  

> Your answer here...

---

**Q4: Why does a C developer have to handle "still reachable" memory explicitly in shutdown code, whereas a C++ developer writing the same module often does not?**  

> Your answer here...

---

**Q5: Walk through a concrete scenario that triggers "Conditional jump or move depends on uninitialised value(s)". What must be true about the data and the control flow for this message to appear?**  

> Your answer here...

---

**Q6: Valgrind's recommended fix order is: `definitely lost` → `indirectly lost` → `still reachable`. Explain the reasoning behind this ordering.**  

> Your answer here...

---

**Q7: When is "still reachable" memory acceptable to leave in a production binary, and when must you still add explicit cleanup? Give one example of each case.**  

> Your answer here...

---

**Q8: How can all functional tests pass while Valgrind reports critical memory issues? What does this reveal about the relationship between correctness testing and memory hygiene?**  

> Your answer here...
