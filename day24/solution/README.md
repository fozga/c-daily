# Day 24 Solution Workspace

## Build and run

- `make test` - build and run scanner tests.
- `make asan` - run tests with AddressSanitizer.
- `make valgrind` - run tests under Valgrind.
- `make clean` - remove generated binaries.

## Answers

1. What does `fgets` do when it reads exactly `buf_size - 1` characters and there are more characters remaining on the line?  
   *Hint: line continuation remains in stream for next read.*  
   > TODO: write your answer here.

2. Why should matching output go to stdout but error messages go to stderr?  
   *Hint: keep data stream clean for redirection/pipelines.*  
   > TODO: write your answer here.

3. When does POSIX grep NOT print the filename prefix?  
   *Hint: single input stream behavior.*  
   > TODO: write your answer here.

4. How do you detect EOF vs an I/O error using `fgets`?  
   *Hint: inspect `feof()` and `ferror()` after NULL return.*  
   > TODO: write your answer here.

5. Why should you strip the trailing newline from a line before matching?  
   *Hint: newline is input formatting, not semantic content in matcher rules.*  
   > TODO: write your answer here.

6. Why should line numbers increment per line read, not per match?  
   *Hint: output line number must reflect original file position.*  
   > TODO: write your answer here.

7. Why design scanner API around `FILE*` rather than filenames directly?  
   *Hint: same function can process stdin and opened files uniformly.*  
   > TODO: write your answer here.

8. What should scanner return on I/O error, and why?  
   *Hint: caller needs explicit failure signal separate from 0 matches.*  
   > TODO: write your answer here.
