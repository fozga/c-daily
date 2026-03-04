# Day 07 Solution Workspace

Implement `parser.c` according to the contracts in `parser.h`. Prioritize deterministic error behavior, explicit return codes, and correct `errno` signaling for range failures.

## Build and test

```bash
make test
make asan
make valgrind
make clean
```

## Answers

**Q1: Why can't C use exceptions for error handling?**  
*Hint: see `../materials/notes.md` -> Section 1*

> 

---

**Q2: Why must you set `errno = 0` before calling functions like `strtol`?**  
*Hint: see `../materials/notes.md` -> Section 2*

> 

---

**Q3: When is it appropriate to use an out-parameter instead of returning data directly?**  
*Hint: see `../materials/notes.md` -> Section 3*

> 

---

**Q4: Why is `errno` implemented as a thread-local variable in modern C runtimes?**  
*Hint: see `../materials/notes.md` -> Section 2*

> 

---

**Q5: What does `EINVAL` typically represent in C/POSIX style APIs?**  
*Hint: see `../materials/notes.md` -> Sections 2 and 5*

> 

---

**Q6: Why are enum-based custom errors useful even when `errno` exists?**  
*Hint: see `../materials/notes.md` -> Section 4*

> 

---

**Q7: Why should API contracts define behavior for `NULL` pointers and malformed input explicitly?**  
*Hint: see `../materials/notes.md` -> Section 5*

> 
