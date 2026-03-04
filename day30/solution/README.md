# Day 30 Solution Workspace

## Build and run

- Build your final `mini-grep` binary first.
- Run: `bash stress_test.sh ./mini-grep`

## Answers

**Q1: In `stress_test.sh`, exit codes 139 and 134 are classified as failures while 0, 1, and 2 are acceptable. What do exit codes 139 and 134 represent at the OS level?**  

> Your answer here...

---

**Q2: Why does feeding raw binary data (e.g., from `/dev/urandom`) to mini-grep require special care with C string functions like `strlen` and `strstr`?**  

> Your answer here...

---

**Q3: `fgets(buf, N, fp)` returns a buffer that does not end with `\n`. What does this indicate, and what must a robust scanner do to handle this case correctly?**  

> Your answer here...

---

**Q4: Why is using `assert()` to validate user-supplied input (such as the pattern argument) unsafe in a release build, and what should be used instead?**  

> Your answer here...

---

**Q5: In the ASan + GDB crash hardening workflow, why must `stress_test.sh` be re-run after each fix rather than moving directly to the next crash?**  

> Your answer here...

---

**Q6: Why should the binary NOT be stripped with `strip` until after all crashes are resolved?**  

> Your answer here...

---

**Q7: The release build uses `-O2 -DNDEBUG`. What does `-DNDEBUG` disable at compile time, and what class of checks should never rely solely on it?**  

> Your answer here...

---

**Q8: Why should a stress test script be run multiple times rather than just once? Name the class of bug that repeated execution helps expose.**  

> Your answer here...
