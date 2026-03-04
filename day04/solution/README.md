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

**Q1: What happens when you use `sizeof` on an array parameter inside a function?**  
*Hint: see `../materials/notes.md` -> Section 2*

> 

---

**Q2: What is the exact relationship between `p[i]` and `*(p + i)` in C?**  
*Hint: see `../materials/notes.md` -> Section 4*

> 

---

**Q3: When you add an integer `k` to pointer `T* p`, what unit does `k` represent?**  
*Hint: see `../materials/notes.md` -> Section 3*

> 

---

**Q4: What type is produced when you subtract two pointers into the same array?**  
*Hint: see `../materials/notes.md` -> Section 3*

> 

---

**Q5: Why must buffer length always be passed alongside a pointer in C APIs?**  
*Hint: see `../materials/notes.md` -> Sections 1 and 5*

> 

---

**Q6: Give one common off-by-one mistake when reading from a fixed buffer and explain its consequence.**  
*Hint: see `../materials/notes.md` -> Section 5*

> 

---

**Q7: Why is `sizeof(ptr) / sizeof(ptr[0])` usually wrong inside a function that takes `int* ptr`?**  
*Hint: see `../materials/notes.md` -> Sections 1 and 2*

> 

---

**Q8: How do raw C arrays/pointers differ from C++ `std::span` regarding size awareness and bounds discipline?**  
*Hint: see `../materials/notes.md` -> C vs C++ callouts across sections*

> 
