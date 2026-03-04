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

**Q1: An API function could return the parsed integer directly, using a sentinel like `-1` to indicate failure. Explain why this design breaks down in practice, and how the out-parameter + status-code pattern avoids the problem.**  

> Your answer here...

---

**Q2: Why must you set `errno = 0` before calling functions like `strtol`?**  

> Your answer here...

---

**Q3: When is it appropriate to use an out-parameter instead of returning data directly?**  

> Your answer here...

---

**Q4: Why is `errno` implemented as a thread-local variable in modern C runtimes?**  

> Your answer here...

---

**Q5: `atoi("42abc")` returns `42` without any error. Describe two additional scenarios where `atoi` silently produces a wrong or ambiguous result, and explain which `strtol` checks prevent each.**  

> Your answer here...

---

**Q6: Why are enum-based custom errors useful even when `errno` exists?**  

> Your answer here...

---

**Q7: Why should API contracts define behavior for `NULL` pointers and malformed input explicitly?**  

> Your answer here...

---

**Q8: A daemon process must report a failed `open()` call. `perror` is unsuitable here. Explain why, and show the correct pattern using `strerror` that captures the error message before any subsequent function call can overwrite `errno`.**  

> Your answer here...
