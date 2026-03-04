# Day 21 Solution Workspace

## Build and run

- `make test` - build and run tests.
- `make asan` - run tests with AddressSanitizer.
- `make valgrind` - run tests with Valgrind.
- `make clean` - remove generated binaries.

## Answers

**Q1: What happens to code with side effects inside `assert(cond)` when the binary is compiled with `-DNDEBUG`? Show the difference with a concrete before/after example.**  

> Your answer here...

---

**Q2: What GCC flag disables all assertions, and where in a build system would you apply it (debug vs release)? What is the risk of disabling assertions too aggressively?**  

> Your answer here...

---

**Q3: Why is a `MALLOC_SEAM` macro plus a controllable test allocator a better approach to OOM testing than simply trying to exhaust real system memory?**  

> Your answer here...

---

**Q4: Define "data structure invariant" and list three invariants that must hold for a valid singly linked list. What does it mean for an invariant check to "fire at the mutation site"?**  

> Your answer here...

---

**Q5: What is the design rule for choosing between `assert` and returning an error code? Give one example of each category and explain why mixing them up causes real problems.**  

> Your answer here...

---

**Q6: Why should `slist_verify_invariants` be called at the end of every mutating function rather than only before reads? What debugging advantage does this placement give you?**  

> Your answer here...

---

**Q7: Describe how the `MALLOC_SEAM` macro allows the same source file to compile correctly for both production and test targets without any `#ifdef` in the business logic itself.**  

> Your answer here...

---

**Q8: What specific failure mode occurs when a test does not reset `test_set_malloc_fail_at(-1)` after an OOM test? Describe a realistic ordering of tests that would expose this as a flaky failure.**  

> Your answer here...
