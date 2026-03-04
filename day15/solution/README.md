# Day 15 Solution Workspace

## Build and run

- `make test` - build and run tests (initially crashes due to intentional bug).
- `make asan` - run tests with AddressSanitizer.
- `make valgrind` - run tests under Valgrind.
- `make clean` - remove generated binaries.

## Bug Report

Paste your GDB findings below:

- Crashing line: `TODO`
- Why it crashes: `TODO`
- 1-sentence fix summary: `TODO`

Example workflow:
- `gdb ./test_runner`
- `run`
- `bt`
- `frame N`
- `print curr`

## Answers

1. What is the difference between `step` and `next` in GDB?  
   *Hint: one enters called functions, the other executes over them.*  
   > TODO: write your answer here.

2. What does the `bt full` command do?  
   *Hint: compare it with plain `bt` output details.*  
   > TODO: write your answer here.

3. How do you inspect the value pointed to by a pointer in GDB?  
   *Hint: dereference expressions with `print`.*  
   > TODO: write your answer here.

4. What is a "frame" in the context of a debugger?  
   *Hint: each function call contributes one stack frame.*  
   > TODO: write your answer here.

5. When would you use a hardware watchpoint instead of a breakpoint?  
   *Hint: think "stop when variable changes", not "stop at line".*  
   > TODO: write your answer here.

6. Why can debugging optimized builds (`-O2`) be misleading?  
   *Hint: variable lifetimes and control flow may be transformed.*  
   > TODO: write your answer here.

7. Why should you inspect both current and caller frames after a segfault?  
   *Hint: crash site may be symptom, not root cause.*  
   > TODO: write your answer here.

8. What is the practical difference between `watch`, `rwatch`, and `awatch`?  
   *Hint: write vs read vs access triggers.*  
   > TODO: write your answer here.
