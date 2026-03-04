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

> Your answer here...

---

**Q2: You are implementing `dstr_append(dyn_string_t* ds, const char* src, size_t src_len)`. After a successful `realloc` that grows the buffer, you must preserve two invariants before returning. Name both invariants and explain what test failure reveals each one is missing.**  

> Your answer here...

---

**Q3: If a function returns a heap-allocated pointer, how do you communicate that the caller must free it?**  

> Your answer here...

---

**Q4: What happens if you call `free` on the same pointer twice?**  

> Your answer here...

---

**Q5: How does C code clean up memory when an error occurs halfway through a function with multiple allocations? Compare this with C++ RAII/exceptions.**  

> Your answer here...

---

**Q6: Why should borrowed pointers (for example from `dstr_get_cstr`) not be freed by the caller?**  

> Your answer here...

---

**Q7: Why must dynamic string code keep NUL termination as an invariant after successful writes?**  

> Your answer here...

---

**Q8: Name two common heap bugs that Valgrind can reveal and explain briefly how they happen.**  

> Your answer here...
