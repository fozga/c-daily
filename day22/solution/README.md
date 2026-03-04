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

1. What is the type of `argv` and what value does `argv[argc]` always hold?  
   *Hint: main signature and array termination guarantee.*  
   > TODO: write your answer here.

2. Should a usage error message be written to stdout or stderr? Why?  
   *Hint: consider shell pipelines and error channel separation.*  
   > TODO: write your answer here.

3. What exit code should a CLI tool return for invalid arguments?  
   *Hint: common POSIX command misuse convention.*  
   > TODO: write your answer here.

4. What is the POSIX convention for when `-` is given as a filename argument?  
   *Hint: many Unix tools treat it as stdin marker.*  
   > TODO: write your answer here.

5. Why is `strcmp(argv[i], "-x") == 0` safer than `argv[i][1] == 'x'`?  
   *Hint: full-string validation avoids malformed short-string reads and ambiguity.*  
   > TODO: write your answer here.

6. Why should option parsing stop once the pattern positional argument is consumed?  
   *Hint: tokens after pattern are files, even if they begin with `-`.*  
   > TODO: write your answer here.

7. Why keep `cli_opts_t` fields as pointers into `argv` instead of allocating new strings here?  
   *Hint: ownership simplicity at parse layer.*  
   > TODO: write your answer here.

8. Why is `-h` usually handled immediately (print usage and exit) in CLI parsers?  
   *Hint: help should not depend on full validity of remaining arguments.*  
   > TODO: write your answer here.
