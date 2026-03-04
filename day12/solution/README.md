# Day 12 Solution Workspace

## Build and run

- `make test` - build and run tests.
- `make asan` - run tests with AddressSanitizer.
- `make layout_check` - rebuild with `-Wpadded` to inspect padding warnings.
- `make valgrind` - run tests under Valgrind.
- `make clean` - remove generated binaries.

## Answers

**Q1: Explain why the compiler inserts padding between `uint8_t flags` and `uint32_t id` in `record_bad_t`. What hardware property makes this necessary, and does the C standard mandate it or leave it ABI-defined?**  

> Your answer here...

---

**Q2: Given `record_bad_t` (sizeof == 12) and `record_good_t` (sizeof == 8), use `offsetof` and `sizeof` values to identify exactly where the 4 bytes of padding live in `record_bad_t`.**  

> Your answer here...

---

**Q3: A colleague proposes using `__attribute__((packed))` to eliminate all padding so structs can be safely written with `fwrite`. List two concrete failure modes this can introduce even on x86.**  

> Your answer here...

---

**Q4: What is "tail padding"? For an array `record_good_t arr[3]`, how many padding bytes total does the compiler insert, and why?**  

> Your answer here...

---

**Q5: You add `_Static_assert(sizeof(record_good_t) == 8, "size changed")` to your code, then a teammate adds a new `uint32_t` field. Describe what the developer sees and why this is better than a runtime test.**  

> Your answer here...

---

**Q6: Two programs on the same machine write and read a struct with `fwrite`/`fread`. It works today. List three changes that could silently break the round-trip in the future without any compiler warning.**  

> Your answer here...

---

**Q7: How does `-Wpadded` differ from checking `sizeof` and `offsetof` manually? When is each approach more useful?**  

> Your answer here...

---

**Q8: Describe a proper field-by-field serialization strategy for `record_good_t` that avoids every padding and alignment hazard discussed in the notes.**  

> Your answer here...

---
