# Day 14 Solution Workspace

## Build and run

- `make lib` - build `libcdrills.a`.
- `make cli` - build the `cdrills` CLI.
- `make run` - run a demo CLI command.
- `make test` - build and run integration smoke tests.
- `make asan` - run smoke tests with AddressSanitizer.
- `make valgrind` - run smoke tests with Valgrind.
- `make clean` - remove binaries, objects, and archive outputs.

## Answers

**Q1: A shared library `.so` and a static library `.a` both provide `store_create`. Describe what happens at link time and at runtime for each, including what happens if the `.so` is missing when the consumer binary is executed.**  

> Your answer here...

---

**Q2: You run `ar rcs libcdrills.a` but forget to include `store.o`. The build succeeds. At what step does the error surface, and what is the exact error message category?**  

> Your answer here...

---

**Q3: Explain step by step why `gcc -L. -lcdrills cli.o -o cdrills` produces "undefined reference" errors while `gcc cli.o -L. -lcdrills -o cdrills` succeeds, even though both commands name the same files.**  

> Your answer here...

---

**Q4: Your umbrella header `cdrills_lib.h` includes all three module headers. A consumer changes a single struct in one module. How many `.c` files are forced to recompile, and how could you reduce that number with forward declarations?**  

> Your answer here...

---

**Q5: The `cmd_parse` subcommand encounters a malformed file and wants to report the error. What exit code should `main` return, and how should the error message be routed (stdout vs stderr) and why?**  

> Your answer here...

---

**Q6: Your unit tests for `store.c` all pass. You then wire `store.c` into `libcdrills.a` and call it from `cli.c`, and it crashes. Name three categories of bugs that integration tests catch that unit tests miss in this scenario.**  

> Your answer here...

---

**Q7: A file named `test` exists in the project directory. What happens when `make test` runs without a `.PHONY: test` declaration? Show the exact make output and explain why.**  

> Your answer here...

---

**Q8: A colleague argues that the dispatch-table approach in the CLI (array of `{name, fn}` pairs) is over-engineering compared to a simple `if/strcmp` chain. Make the case for and against the dispatch table, considering extensibility and testability.**  

> Your answer here...

---
