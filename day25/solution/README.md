# Day 25 Solution Workspace

## Build and run

- `make test` - build and run diagnostics tests.
- `make asan` - run tests with AddressSanitizer.
- `make valgrind` - run tests under Valgrind.
- `make clean` - remove generated binaries.

## Answers

1. Why must you read `errno` immediately after the failing call?  
   *Hint: later library calls can overwrite thread-local errno state.*  
   > TODO: write your answer here.

2. What is the difference between `perror` and `strerror`?  
   *Hint: one prints directly with prefix, the other returns text string.*  
   > TODO: write your answer here.

3. If 3 files are processed and 1 fails to open, should the tool exit 0 or 1?  
   *Hint: partial failure should be reflected in final status.*  
   > TODO: write your answer here.

4. What exit code does real POSIX grep use when no lines are matched?  
   *Hint: it is non-zero but not usage-error tier.*  
   > TODO: write your answer here.

5. What format should diagnostic messages follow for good UX?  
   *Hint: include program name, context, and reason text.*  
   > TODO: write your answer here.

6. Why should diagnostics be printed to stderr, not stdout?  
   *Hint: preserve clean match output for pipelines and file redirection.*  
   > TODO: write your answer here.

7. Why continue processing remaining files after one open failure?  
   *Hint: maximize useful output from valid inputs in Unix tool style.*  
   > TODO: write your answer here.

8. Why distinguish "only errors" from "no matches but no errors" in exit-code design?  
   *Hint: scripts may react differently to semantic no-match vs operational failure.*  
   > TODO: write your answer here.
