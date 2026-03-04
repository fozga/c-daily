# Day 13 Solution Workspace

## Build and run

- `make test` - build and run tests.
- `make asan` - run tests with AddressSanitizer.
- `make valgrind` - run tests under Valgrind.
- `make clean` - remove generated binaries.

## Answers

**Q1: A consumer declares `store_t *s` using only `store.h`. Explain precisely why `s->count` fails to compile, even though `count` does exist in the struct. What mechanism enforces this at the language level?**  

> Your answer here...

---

**Q2: Two `.c` files both define a `static` function called `hash_key`. Will this cause a linker error? Contrast this with what would happen if both functions were non-`static`.**  

> Your answer here...

---

**Q3: You want to change `store_t`'s internal hash table from linear probing to chaining. With the opaque pattern, which files must be recompiled? If the struct were fully public in `store.h`, what additional files would need to be recompiled or changed?**  

> Your answer here...

---

**Q4: Describe an ABI-level scenario where a public struct causes a binary-compatibility break that an opaque handle would have prevented. (Assume a pre-compiled consumer library.)**  

> Your answer here...

---

**Q5: `store_create` can fail and return NULL. Write out the idiomatic NULL-check pattern a caller should use, and explain why `store_destroy(NULL)` being safe matters for error-path cleanup.**  

> Your answer here...

---

**Q6: A junior engineer adds `#include "store_internal.h"` to `tests.c` "just to inspect the count field". Explain the concrete maintenance and correctness risks this introduces.**  

> Your answer here...

---

**Q7: Compare the opaque C handle pattern to C++'s PIMPL idiom. What does each approach guarantee at the language level vs at the convention level?**  

> Your answer here...

---

**Q8: You are designing a `store_foreach` iterator that visits every key-value pair. Should it accept a function pointer callback or return an iterator struct? Discuss the tradeoffs in terms of encapsulation and ease of use for the caller.**  

> Your answer here...

---
