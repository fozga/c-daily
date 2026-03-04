# Day 16 Solution Workspace

## Build and run

- `make test` - run baseline tests (may pass despite hidden memory bugs).
- `make asan` - run AddressSanitizer build and inspect bug reports.
- `make valgrind` - optional secondary runtime memory checks.
- `make clean` - remove generated binaries.

## Bugs Found

Document the three bugs you identify and fix:

1. `<bug 1: symptom + root cause + fix>`
2. `<bug 2: symptom + root cause + fix>`
3. `<bug 3: symptom + root cause + fix>`

## Answers

**Q1: What is "shadow memory" in ASan, and how does it let the runtime detect an out-of-bounds access in constant time regardless of allocation size?**  

> Your answer here...

---

**Q2: What is a redzone, and why does ASan place redzones both before and after an allocation rather than only at the end?**  

> Your answer here...

---

**Q3: Why does ASan need to intercept `malloc` and `free`, and what would be missing from use-after-free reports if it did not track allocation lifetimes?**  

> Your answer here...

---

**Q4: Explain the heap-use-after-free bug class. Walk through what the three stack traces in a UAF report represent and in what order you should read them.**  

> Your answer here...

---

**Q5: Name one memory error class that ASan catches reliably but Valgrind Memcheck typically cannot detect. Explain why the architectural difference causes this gap.**  

> Your answer here...

---

**Q6: Why does `-fno-omit-frame-pointer` improve the quality of ASan stack traces, and what can you lose if you omit it in a stack-heavy program?**  

> Your answer here...

---

**Q7: An ASan report says `WRITE of size 1 at 0x...`. What three things does that single line tell you, and which additional section of the report identifies the root cause?**  

> Your answer here...

---

**Q8: Why can a test suite pass without ASan even though severe memory bugs are present? What property of undefined behavior (UB) in C makes this possible?**  

> Your answer here...
