# Day 05 Solution Workspace

Implement the `strview` API in `strview.c` using only pointer+length logic. Do not rely on NUL-termination in algorithm loops.

## Build and test

```bash
make test
make asan
make valgrind
make clean
```

## Answers

**Q1: Why is `strlen()` an O(N) operation?**  
*Hint: see `../materials/notes.md` -> Section 2*

> 

---

**Q2: What happens if you pass a string without a `\0` to a standard C function expecting a C-string?**  
*Hint: see `../materials/notes.md` -> Sections 1 and 2*

> 

---

**Q3: Why is a String View struct typically faster for taking substrings than a standard C-string approach?**  
*Hint: see `../materials/notes.md` -> Section 3*

> 

---

**Q4: How do you calculate the length of a substring given a start pointer and an end pointer?**  
*Hint: see `../materials/notes.md` -> Section 5*

> 

---

**Q5: Why is `printf("%s", view.data)` dangerous for generic `strview` data?**  
*Hint: see `../materials/notes.md` -> Sections 1 and 3*

> 

---

**Q6: Conceptually, why is view equality closer to `memcmp` than `strcmp`?**  
*Hint: see `../materials/notes.md` -> Section 4*

> 

---

**Q7: In a C API, why must pointer lifetime and view length both be part of the contract?**  
*Hint: see `../materials/notes.md` -> Sections 3 and 5*

> 
