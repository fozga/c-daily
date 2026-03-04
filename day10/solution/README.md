# Day 10 Solution Workspace

## Build and run

- `make test` - build and run tests.
- `make asan` - run tests with AddressSanitizer.
- `make valgrind` - run tests under Valgrind.
- `make clean` - remove generated binaries.

## Answers

**Q1: On Linux, opening a file in text mode (`"w"`) vs binary mode (`"wb"`) produces the same bytes. Why is it still important to always use `"rb"`/`"wb"` for binary files?**  

> Your answer here...

---

**Q2: `fread(&hdr, sizeof hdr, 1, fp)` returns `0` on the very first read of a newly created file. Walk through the decision tree: what do `feof` and `ferror` each tell you, and which return code should you give the caller?**  

> Your answer here...

---

**Q3: A struct contains `int count` and is written to disk with `fwrite`. Six months later the codebase is ported to a 64-bit embedded target where `int` is 16 bits. What exactly breaks, and how would `uint32_t` have prevented it?**  

> Your answer here...

---

**Q4: Describe a concrete attack or data-corruption scenario that magic-byte validation prevents. What additional protection does version validation add on top of magic validation?**  

> Your answer here...

---

**Q5: Write a short C snippet that detects at runtime whether the host system is little-endian or big-endian. Explain how it works at the byte level.**  

> Your answer here...

---

**Q6: A file header declares `rec_count = 1000000` but the file is only 512 bytes. Why is checking `rec_count` against a sane upper bound before calling `fread` essential, even though `fread` will simply short-return?**  

> Your answer here...

---

**Q7: You call `fread(buf, rec_size, n, fp)` and it returns `n-2`. How do you determine whether the two missing records were caused by end-of-file or by a mid-file I/O error, and why does it matter?**  

> Your answer here...

---

**Q8: The example uses `__attribute__((packed))` on the on-disk header struct. What risk does this introduce, and what is a safer alternative for defining portable binary layouts?**  

> Your answer here...

---
