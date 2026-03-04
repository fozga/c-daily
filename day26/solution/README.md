# Day 26 Solution Workspace

## Build and run

- `make build` - build `mini-grep` from integrated project sources.
- `make test` - run integration matrix script.
- `make clean` - remove built binary.

Direct invocation:
- `bash test_matrix.sh ./mini-grep`

## Answers

1. What is the difference between an integration test and a unit test?  
   *Hint: isolation level and system boundary scope differ.*  
   > TODO: write your answer here.

2. How do you check the exit code of a command in a shell script?  
   *Hint: inspect `$?` immediately after command execution.*  
   > TODO: write your answer here.

3. What makes a good regression test?  
   *Hint: deterministic, focused, and tied to a previously observed bug.*  
   > TODO: write your answer here.

4. What are the risks of golden/snapshot testing?  
   *Hint: can become brittle when output formatting changes intentionally.*  
   > TODO: write your answer here.

5. What CLI behaviors are difficult to test with unit tests and require integration testing?  
   *Hint: process-level behavior like exit codes/stdout/stderr formatting.*  
   > TODO: write your answer here.

6. Why should integration tests validate stderr separately from stdout?  
   *Hint: data output and diagnostics serve different consumers.*  
   > TODO: write your answer here.

7. Why should fixture files be committed and stable over time?  
   *Hint: reproducibility of failures and CI consistency.*  
   > TODO: write your answer here.

8. Why should a test matrix include both success and failure scenarios?  
   *Hint: robustness includes correct handling of invalid inputs and errors.*  
   > TODO: write your answer here.
