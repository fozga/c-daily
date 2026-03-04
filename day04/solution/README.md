# Day 04 Solution Workspace

Implement the fixed-buffer parser API declared in `buffer.h` by completing `buffer.c` and validating behavior through tests.

## Build and test

```bash
make test
make asan
make valgrind
make clean
```

## Answers

**Q1: A helper function `size_t count_elems(int arr[]) { return sizeof(arr) / sizeof(arr[0]); }` always returns `2` on a 64-bit system where `sizeof(int)==4`, regardless of how many elements were passed. Explain the two language rules that combine to produce this result.**  

> Your answer here...

---

**Q2: You are writing a copy function that reads `n` bytes from `src` starting at offset `cursor`. Before the read, you check `cursor + n > cap`. Under what arithmetic condition does this check itself contain a bug, and what is the correct way to write it?**  

> Your answer here...

---

**Q3: When you add an integer `k` to pointer `T* p`, what unit does `k` represent?**  

> Your answer here...

---

**Q4: What type is produced when you subtract two pointers into the same array?**  

> Your answer here...

---

**Q5: Why must buffer length always be passed alongside a pointer in C APIs?**  

> Your answer here...

---

**Q6: Give one common off-by-one mistake when reading from a fixed buffer and explain its consequence.**  

> Your answer here...

---

**Q7: Why is `sizeof(ptr) / sizeof(ptr[0])` usually wrong inside a function that takes `int* ptr`?**  

> Your answer here...

---

**Q8: How do raw C arrays/pointers differ from C++ `std::span` regarding size awareness and bounds discipline?**  

> Your answer here...
