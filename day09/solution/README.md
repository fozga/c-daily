# Day 09 Solution Workspace

## Build and run

- `make test` - build and run tests.
- `make asan` - run tests with AddressSanitizer.
- `make valgrind` - run tests under Valgrind.
- `make clean` - remove generated binaries.

## Answers

1. Why is `scanf("%s", buf)` dangerous?  
   *Hint: think about missing width limits and buffer boundaries.*  
   > TODO: write your answer here.

2. Why must you set `errno = 0` before calling `strtol`?  
   *Hint: `errno` persists from prior library calls.*  
   > TODO: write your answer here.

3. How do you detect that `strtol` consumed all characters (no trailing garbage)?  
   *Hint: inspect `endptr` after conversion.*  
   > TODO: write your answer here.

4. What does `fgets` do with the newline character at the end of a line?  
   *Hint: consider whether the newline fits in the destination buffer.*  
   > TODO: write your answer here.

5. What is the difference between `feof` and `ferror`?  
   *Hint: EOF is normal stream exhaustion; I/O error is not.*  
   > TODO: write your answer here.

6. Why is parsing full lines first usually better than token-by-token stdin scanning?  
   *Hint: think control flow, validation quality, and error recovery.*  
   > TODO: write your answer here.

7. What checks are needed before narrowing `strtol` output into `int32_t`?  
   *Hint: range-check against target type limits after conversion.*  
   > TODO: write your answer here.

8. How should malformed CSV-like lines be handled in a robust parser?  
   *Hint: return explicit error codes for each failure class.*  
   > TODO: write your answer here.
