# Day 01 Solution Workspace

Purpose: implement a small multi-file C11 exercise and practice the full GCC + Make workflow (compile, test, sanitize, and memory-check).

Create these files in this directory:

- `main.c`
- `util.c`
- `util.h`
- `tests.c`

Suggested implementation flow:

1. Implement a string reversal function in `util.c`.
2. Expose its declaration in `util.h` with proper include guards.
3. Call it from `main.c` for a manual run.
4. Write at least 3 assertions in `tests.c`.

## How to run

```bash
make test
make asan
make valgrind
make clean
```

## Answers

**Q1: What are the 4 stages of the GCC compilation pipeline?**  
*Hint: see notes.md -> Section 1*

> Your answer here...

---

**Q2: You compiled `main.c` successfully, but linker reports `undefined reference to util_reverse_string`. What is the most likely cause?**  
*Hint: see notes.md -> Section 1*

> Your answer here...

---

**Q3: What command runs only preprocessing for `main.c` so you can inspect expanded includes/macros?**  
*Hint: see notes.md -> Section 1*

> Your answer here...

---

**Q4: What should go into `util.h`, and what should usually stay out of headers?**  
*Hint: see notes.md -> Section 2*

> Your answer here...

---

**Q5: Why do include guards prevent multiple definition/redefinition problems?**  
*Hint: see notes.md -> Section 2*

> Your answer here...

---

**Q6: How is `#include <stdio.h>` different from `#include "util.h"` in header search behavior?**  
*Hint: see notes.md -> Section 2*

> Your answer here...

---

**Q7: What is the practical difference between `-Wall` and `-Wextra`, and why is `-Wall` not enough alone?**  
*Hint: see notes.md -> Section 3*

> Your answer here...

---

**Q8: Which flag turns warnings into build failures, and why is that useful in daily practice?**  
*Hint: see notes.md -> Section 3*

> Your answer here...

---

**Q9: You suspect a variable is accidentally shadowed in an inner scope. Which warning flag should you add?**  
*Hint: see notes.md -> Section 3*

> Your answer here...

---

**Q10: What information does `-g` add to a binary, and how does GDB use it?**  
*Hint: see notes.md -> Section 4*

> Your answer here...

---

**Q11: Why is `-O0 -g` preferred for debugging over `-O2 -g`?**  
*Hint: see notes.md -> Section 4*

> Your answer here...

---

**Q12: In a Make rule, what do `$@`, `$^`, and `$<` expand to?**  
*Hint: see notes.md -> Section 5*

> Your answer here...

---

**Q13: Why should targets like `test` and `clean` be listed under `.PHONY`?**  
*Hint: see notes.md -> Section 5*

> Your answer here...

---

**Q14: What kinds of memory bugs does AddressSanitizer catch, and what flag must be present at both compile and link time?**  
*Hint: see notes.md -> Section 6*

> Your answer here...

---

**Q15: Why should Valgrind Memcheck be run on a non-ASan debug build, and which leak category is the strongest fix-now signal?**  
*Hint: see notes.md -> Section 7*

> Your answer here...
