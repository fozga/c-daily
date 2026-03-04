# Day 20 Solution Workspace

## Build and run

- `make test` - build and run tests.
- `make asan` - run tests with AddressSanitizer.
- `make valgrind` - run tests with Valgrind.
- `make clean` - remove generated binaries.

## Answers

**Q1: Why is right-shifting a negative signed integer implementation-defined behavior in C, and what concrete difference in machine output can you observe between an arithmetic shift and a logical shift on `-1 >> 1`?**  

> Your answer here...

---

**Q2: Explain two distinct categories of undefined behavior (UB) that can arise from using a signed integer type for bit manipulation. Give one concrete example of each.**  

> Your answer here...

---

**Q3: Why is `1 << 40` a bug on a platform where `int` is 32 bits? What is the fix, and why does `(uint64_t)1 << 40` also work while `1UL << 40` may not be portable?**  

> Your answer here...

---

**Q4: Given a `uint64_t` block array and a global bit index, write out in full the expression for computing `block_index` and `bit_offset`, then write the complete `bitset_set` expression using those values.**  

> Your answer here...

---

**Q5: Why does clearing a bit require `x &= ~mask` rather than `x &= mask`? Show by example what `x &= mask` actually does to a word where multiple bits are set.**  

> Your answer here...

---

**Q6: How do you compute block index and bit offset for a global bit index in a `uint64_t` bitset? Why is integer division by 64 equivalent to a right-shift by 6, and when would you prefer one over the other?**  

> Your answer here...

---

**Q7: XOR (`^`) is the natural toggle operator. Explain *why* XOR with a single-bit mask flips exactly that bit and leaves all others unchanged — derive the result from the XOR truth table.**  

> Your answer here...

---

**Q8: What happens — in precise C standard terms — when `bitset_set` receives an out-of-range bit index and no bounds check is performed? Why can the resulting memory corruption be silent and only manifest much later?**  

> Your answer here...
