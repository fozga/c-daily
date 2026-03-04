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

> Your answer here...

---

**Q2: What is the difference between `const int* p` and `int* const p`?**  

> Your answer here...

---

**Q3: A function is declared `void vec_scale(float* restrict out, const float* restrict in, size_t n)`. A caller writes `vec_scale(buf, buf, n)`. Explain what invariant this call violates, why the compiler cannot detect it, and what class of bug it can introduce.**  

> Your answer here...

---

**Q4: What does `restrict` tell the compiler, and what happens if the promise is violated?**  

> Your answer here...

---

**Q5: How does pointer arithmetic scale with underlying type size? Give an `int*` example.**  

> Your answer here...

---

**Q6: Why can two pointers to the same array element create optimization constraints for the compiler?**  

> Your answer here...

---

**Q7: In C, what are the three storage durations you use most often, and how do they affect pointer validity?**  

> Your answer here...

---

**Q8: C++ references cannot be reseated; C pointers can. How does this influence API design and defensive checks in C?**  

> Your answer here...
