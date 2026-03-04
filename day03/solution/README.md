# Day 03 Solution Workspace

Implement all API functions declared in `pointers.h` inside `pointers.c`, then validate behavior with tests and memory tools.

## Build and test

```bash
make test
make asan
make valgrind
make clean
```

## Answers

**Q1: Why is returning a pointer to a local variable undefined behavior in C?**  
*Hint: see `../materials/notes.md` -> Section 2*

> 

---

**Q2: What is the difference between `const int* p` and `int* const p`?**  
*Hint: see `../materials/notes.md` -> Section 5*

> 

---

**Q3: What happens if you pass `NULL` to a function that unconditionally dereferences that pointer?**  
*Hint: see `../materials/notes.md` -> Section 5*

> 

---

**Q4: What does `restrict` tell the compiler, and what happens if the promise is violated?**  
*Hint: see `../materials/notes.md` -> Section 3*

> 

---

**Q5: How does pointer arithmetic scale with underlying type size? Give an `int*` example.**  
*Hint: see `../materials/notes.md` -> Section 4*

> 

---

**Q6: Why can two pointers to the same array element create optimization constraints for the compiler?**  
*Hint: see `../materials/notes.md` -> Section 3*

> 

---

**Q7: In C, what are the three storage durations you use most often, and how do they affect pointer validity?**  
*Hint: see `../materials/notes.md` -> Section 2*

> 

---

**Q8: C++ references cannot be reseated; C pointers can. How does this influence API design and defensive checks in C?**  
*Hint: see `../materials/notes.md` -> Section 1*

> 
