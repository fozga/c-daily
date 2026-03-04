# Day 23 Solution Workspace

## Build and run

- `make test` - build and run matcher tests.
- `make asan` - run tests with AddressSanitizer.
- `make valgrind` - run tests under Valgrind.
- `make clean` - remove generated binaries.

## Answers

1. What is the worst-case complexity of the naive substring search algorithm?  
   *Hint: compare every possible start position against pattern length.*  
   > TODO: write your answer here.

2. Why is `tolower()` not safe for non-ASCII characters?  
   *Hint: locale/Unicode case folding is broader than single-byte ASCII mapping.*  
   > TODO: write your answer here.

3. Should an empty pattern match every line or no lines?  
   *Hint: choose and justify a consistent search semantics.*  
   > TODO: write your answer here.

4. What does it mean to "search" vs "match" a line?  
   *Hint: substring existence vs full-string equivalence.*  
   > TODO: write your answer here.

5. How do you handle the case where the pattern is longer than the line?  
   *Hint: no valid start positions exist; return no-match safely.*  
   > TODO: write your answer here.

6. Why should wildcard `.` logic be implemented in the inner comparison loop, not preprocessed away?  
   *Hint: matching depends on alignment at each candidate start position.*  
   > TODO: write your answer here.

7. Why cast to `unsigned char` before passing to `tolower`?  
   *Hint: negative signed-char values are undefined for ctype macros/functions.*  
   > TODO: write your answer here.

8. Why should matcher code avoid modifying input `line` and `pattern` buffers?  
   *Hint: ownership/const correctness and caller expectations.*  
   > TODO: write your answer here.
