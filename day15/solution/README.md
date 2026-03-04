# Day 15 Solution Workspace

## Build and run

- `make test` - build and run tests (initially crashes due to intentional bug).
- `make asan` - run tests with AddressSanitizer.
- `make valgrind` - run tests under Valgrind.
- `make clean` - remove generated binaries.

## Bug Report

Paste your GDB findings below:

- Crashing line: `<file>:<line>`
- Why it crashes: `<short root-cause explanation>`
- 1-sentence fix summary: `<what you changed and why>`

Example workflow:
- `gdb ./test_runner`
- `run`
- `bt`
- `frame N`
- `print curr`

## Answers

**Q1: What is the difference between `step` and `next` in GDB, and when would choosing the wrong one cause you to skip over the function where the bug actually lives?**  

> Your answer here...

---

**Q2: What extra information does `bt full` show compared to plain `bt`, and how can that additional information change your diagnosis of a segfault?**  

> Your answer here...

---

**Q3: How would you use GDB's `print` and `x` commands together to diagnose a corrupted singly linked list — for example, to verify that each node's `next` pointer actually refers to valid heap memory before the crash occurs?**  

> Your answer here...

---

**Q4: What is a stack frame, and why do local variables from frame `#0` differ from those in frame `#1` even when the two functions are closely related?**  

> Your answer here...

---

**Q5: When would you use a hardware watchpoint instead of a breakpoint? Describe a concrete scenario where a watchpoint would catch a bug that a breakpoint at the crash site would not.**  

> Your answer here...

---

**Q6: Why can debugging an optimized build (`-O2`) be misleading, and what two specific GDB behaviors change compared to a `-O0 -g` build?**  

> Your answer here...

---

**Q7: After a segfault, why should you examine caller frames and not just the crash frame at the top of `bt`? Illustrate with the example from the notes.**  

> Your answer here...

---

**Q8: What is the practical difference between `watch`, `rwatch`, and `awatch` in GDB? Describe a scenario where `rwatch` would detect a bug that `watch` would miss.**  

> Your answer here...
