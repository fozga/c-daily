# Day 25 Solution Workspace

## Build and run

- `make test` - build and run diagnostics tests.
- `make asan` - run tests with AddressSanitizer.
- `make valgrind` - run tests under Valgrind.
- `make clean` - remove generated binaries.

## Answers

**Q1: `diag_open_file` calls `fopen`, then `fprintf` to print the error. Why must `errno` be saved into a local variable before the `fprintf` call?**

> Your answer here...

---

**Q2: `perror("mini-grep")` produces `mini-grep: No such file or directory` for a missing file, but mini-grep's spec requires `mini-grep: foo.txt: No such file or directory`. Why doesn't `perror` satisfy the spec, and what does `diag_open_file` use instead?**

> Your answer here...

---

**Q3: mini-grep processes `a.txt` (matches found), `b.txt` (cannot open), and `c.txt` (no matches). What is the correct final exit code, and which row of the exit-code table applies?**

> Your answer here...

---

**Q4: A shell script runs `mini-grep "TODO" src/*.c; if [ $? -eq 1 ]; then echo "No TODOs found"; fi`. Under what two distinct conditions will mini-grep exit `1`, and could the script misinterpret one of them?**

> Your answer here...

---

**Q5: mini-grep processes five files but exits before finishing the third because the programmer wrote `exit(2)` inside `diag_open_file`. What Unix tool principle does this violate, and how should it be fixed?**

> Your answer here...

---

**Q6: A user runs `mini-grep "err" app.log 2>/dev/null | head -5`. If diagnostic messages were sent to stdout instead of stderr, what would the pipeline output contain that the user didn't want?**

> Your answer here...

---

**Q7: `main.c` tracks two boolean flags: `any_match` and `any_error`. Why is a single `exit_code` integer insufficient to correctly implement the four-scenario exit mapping?**

> Your answer here...

---

**Q8: POSIX grep exits `2` for an error. mini-grep exits `2` only when ALL files fail and there are no matches. What is the practical difference for a script that wants to distinguish "nothing matched" from "something went wrong"?**

> Your answer here...

---
