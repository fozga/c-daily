# Day 34 Solution Workspace

## Build and run

From this directory:

```bash
make test
make asan
make valgrind
make clean
```

## Answers

**Q1: Explain why a ring buffer with `head == tail` cannot simultaneously represent "full" and "empty" without additional information. What are the two standard solutions, and what is the tradeoff of each?**  

> Your answer here...

---

**Q2: With `RB_CAPACITY = 8`, trace `head` and `tail` through: push A, push B, push C, pop, push D, pop, pop, push E. What is the state of the buffer after each operation? At what point, if any, is it full?**  

> Your answer here...

---

**Q3: Why must `rb_push` check `rb_full` *before* writing to `buf[head]`, rather than after? Describe the exact data-corruption scenario if the check is omitted.**  

> Your answer here...

---

**Q4: Rewrite `head = (head + 1) % 32` as a bitwise expression and prove the two are equivalent for all non-negative `head`.**  

> Your answer here...

---

**Q5: An ISR calls `rb_push` while the main loop concurrently calls `rb_pop`. The buffer uses plain (non-atomic) `size_t` indexes. Describe the race condition and name two mitigation strategies.**  

> Your answer here...

---

**Q6: A developer sizes the ring buffer at exactly the number of bytes they expect the ISR to produce in one burst. After running the system, they observe dropped bytes. What invariant did they violate, and how should they resize the buffer?**  

> Your answer here...

---

**Q7: Why do `rb_push` and `rb_pop` both run in O(1) time regardless of how many bytes are currently stored? Contrast this with a queue implemented as a `memmove`-shifted array.**  

> Your answer here...

---

**Q8: A UART ring buffer holds 255 bytes (`RB_CAPACITY = 256`, one-empty-slot rule). The baud rate is 115200 bps (≈ 11,520 bytes/s). If the main loop processes bytes at 10,000 bytes/s, how long until the buffer overflows from a continuous stream? What design change would prevent data loss?**  

> Your answer here...

---
