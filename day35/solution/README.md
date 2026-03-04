# Day 35 Solution Workspace

## Build and run

From this directory:

```bash
make test
make asan
make valgrind
make clean
```

## Answers

**Q1: A callback registered with `void *ctx = &local_var` where `local_var` is a stack variable in `main`. The callback is fired after `main` returns `local_var` to a different scope. Describe the resulting bug and how `void *ctx` ownership should be documented or enforced.**  

> Your answer here...

---

**Q2: Explain exactly why the compiler is allowed to eliminate the loop condition `while (!g_exit_requested)` when `g_exit_requested` is a plain `int` not marked `volatile`. Name the C standard clause that permits this optimisation.**  

> Your answer here...

---

**Q3: `volatile sig_atomic_t` is used for the exit flag in this day, but Day 32 used `_Atomic` for shared indexes. Under what condition would `volatile sig_atomic_t` be *insufficient* and `_Atomic` *necessary*? When is the reverse true?**  

> Your answer here...

---

**Q4: `dispatch_fire_event` iterates all registered slots and calls every handler whose `event_id` matches. A callback registered inside that iteration (re-entrant registration) could cause subtle bugs. Describe two specific failure scenarios and propose a defensive design.**  

> Your answer here...

---

**Q5: The ISR-safe UART receive pattern uses a ring buffer push inside the ISR and a ring buffer pop in the main loop. Describe, step by step, the race that occurs if both `rb_push` and `rb_pop` run concurrently on a non-atomic ring buffer, and explain which of the two mitigation strategies from Day 34 applies here.**  

> Your answer here...

---

**Q6: A developer wants to call `printf` inside a signal handler to log which signal fired. Explain why this is unsafe in terms of reentrancy and the POSIX async-signal-safety list. What is the correct pattern for logging from an ISR-like context?**  

> Your answer here...

---

**Q7: The `dispatch_register` function stores both a `handler` function pointer and a `ctx` pointer. If the dispatcher is used across a thread boundary (one thread fires events, another registers handlers), what synchronisation is required and why is no synchronisation still wrong even if the thread schedules perfectly?**  

> Your answer here...

---

**Q8: Reflect on the full 35-day arc. You implemented: string manipulation, dynamic arrays, hash maps, a CLI tool, I/O pipelines, threads, lock-free queues, memory pools, FSMs, ring buffers, and event dispatchers. Identify one design pattern or low-level mechanism that appeared in more than three days in different forms, and explain the common underlying principle.**  

> Your answer here...

---
