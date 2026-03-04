# Day 22 Solution Workspace

## Build and run

- `make test` - build parser tests and run them.
- `make build` - build the `mini-grep` CLI binary.
- `make asan` - run parser tests with AddressSanitizer.
- `make valgrind` - run parser tests with Valgrind.
- `make clean` - remove binaries and object files.

## Note
This code is the foundation for days 23–30. Do not throw it away.

## Answers

**Q1: After `getopt` returns `-1`, what does `optind` point to, and how does your `cli_parse` use it to locate mini-grep's PATTERN argument?**

> Your answer here...

---

**Q2: mini-grep exits `2` for an unknown flag but `1` for a missing PATTERN. Why are different exit codes appropriate for these two failure modes?**

> Your answer here...

---

**Q3: For the invocation `mini-grep -n -i "foo" file1.txt file2.txt`, what is `opts->pattern`, what is `opts->files_count`, and which `argv` index is `opts->files[0]`?**

> Your answer here...

---

**Q4: What is the POSIX convention when `-` is supplied as a filename argument to a CLI tool?**

> Your answer here...

---

**Q5: Why is `strcmp(argv[i], "-n") == 0` safer than testing `argv[i][1] == 'n'` when parsing mini-grep flags?**

> Your answer here...

---

**Q6: After PATTERN is consumed from `argv`, a file called `-log.txt` should be treated as a filename, not a flag. What property of your parsing loop ensures this?**

> Your answer here...

---

**Q7: `cli_opts_t` stores `const char *pattern` as a pointer into `argv` rather than a `strdup`-ed copy. What are the lifetime and ownership implications of this choice?**

> Your answer here...

---

**Q8: mini-grep's `-h` flag prints to stdout and exits `0`, while a missing PATTERN prints to stderr and exits `1`. What design principle justifies this difference?**

> Your answer here...

---
