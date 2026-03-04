# Day 06 Solution Workspace

Implement `dyn_string.c` using explicit heap ownership rules. Preserve invariants: valid buffer pointer, consistent `length/capacity`, and a terminating `\0` after successful appends.

## Build and test

```bash
make test
make asan
make valgrind
make clean
```

## Answers

**Q1: Why is `ptr = realloc(ptr, new_size);` a dangerous pattern?**  
*Hint: see `../materials/notes.md` -> Section 3*

> 

---

**Q2: What is the difference between `malloc` and `calloc`?**  
*Hint: see `../materials/notes.md` -> Section 1*

> 

---

**Q3: If a function returns a heap-allocated pointer, how do you communicate that the caller must free it?**  
*Hint: see `../materials/notes.md` -> Section 2*

> 

---

**Q4: What happens if you call `free` on the same pointer twice?**  
*Hint: see `../materials/notes.md` -> Section 4*

> 

---

**Q5: How does C code clean up memory when an error occurs halfway through a function with multiple allocations? Compare this with C++ RAII/exceptions.**  
*Hint: see `../materials/notes.md` -> Sections 5 and C vs C++ callouts*

> 

---

**Q6: Why should borrowed pointers (for example from `dstr_get_cstr`) not be freed by the caller?**  
*Hint: see `../materials/notes.md` -> Section 2*

> 

---

**Q7: Why must dynamic string code keep NUL termination as an invariant after successful writes?**  
*Hint: see `../materials/notes.md` -> Sections 1 and 5*

> 

---

**Q8: Name two common heap bugs that Valgrind can reveal and explain briefly how they happen.**  
*Hint: see `../materials/notes.md` -> Section 4*

> 
