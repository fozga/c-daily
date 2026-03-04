# Day 24 Solution Workspace

## Build and run

- `make test` - build and run scanner tests.
- `make asan` - run tests with AddressSanitizer.
- `make valgrind` - run tests under Valgrind.
- `make clean` - remove generated binaries.

## Answers

**Q1: `fgets` fills a 4096-byte buffer but the line is 5000 bytes long. What exactly is left in the stream after the first call, and what does your scanner do on the next iteration?**

> Your answer here...

---

**Q2: A user runs `mini-grep "error" app.log > matches.txt`. If diagnostic messages go to stdout, what problem does this cause? What is the fix?**

> Your answer here...

---

**Q3: mini-grep is invoked with two files: `mini-grep "foo" a.txt b.txt`. The first match is on line 3 of `a.txt`. What does the output line look like without `-n`, and what does it look like with `-n`?**

> Your answer here...

---

**Q4: `fgets` returns `NULL` after scanning a file. How do you tell whether it stopped due to EOF or an I/O error, and why does the distinction matter for mini-grep's exit code?**

> Your answer here...

---

**Q5: Pattern `"done"` must match a line containing `"done"` but not fail on `"done\n"` (raw line from fgets). Describe the exact stripping idiom and why two separate checks are needed for CRLF files.**

> Your answer here...

---

**Q6: A file has 100 lines; only lines 7, 42, and 99 match. If line numbers are printed, what are the correct numbers, and what goes wrong if you only increment the counter on match?**

> Your answer here...

---

**Q7: `scanner_run` takes `FILE *fp` rather than a `const char *filename` to open internally. What does this design choice enable that a filename-based API cannot provide as cleanly?**

> Your answer here...

---

**Q8: `scanner_run` returns `-1` on I/O error and `0` or `1` on clean completion. Why can't the caller just check the match count to detect an I/O problem?**

> Your answer here...

---
