# Day 10 Solution Workspace

## Build and run

- `make test` - build and run tests.
- `make asan` - run tests with AddressSanitizer.
- `make valgrind` - run tests under Valgrind.
- `make clean` - remove generated binaries.

## Answers

1. Why should you always use `"rb"` and `"wb"` for binary files?  
   *Hint: think about platform-specific text-mode transformations.*  
   > TODO: write your answer here.

2. What does `fread` return if the file ends mid-record?  
   *Hint: return value counts full items, not partial bytes.*  
   > TODO: write your answer here.

3. Why is using `int` as a binary format field a portability bug?  
   *Hint: size and representation of `int` vary by ABI/platform.*  
   > TODO: write your answer here.

4. What are "magic bytes" and why are they useful?  
   *Hint: they identify expected file type before parsing payload.*  
   > TODO: write your answer here.

5. How do you detect endianness at runtime in C?  
   *Hint: inspect byte order of a known multi-byte integer value.*  
   > TODO: write your answer here.

6. Why should unknown binary format versions be rejected?  
   *Hint: unsupported layouts can be misinterpreted silently.*  
   > TODO: write your answer here.

7. What is the difference between `feof` and `ferror` after short reads?  
   *Hint: distinguish expected stream end from actual I/O failure.*  
   > TODO: write your answer here.

8. Why are fixed-width types (`uint32_t`, `int32_t`) critical in binary layouts?  
   *Hint: deterministic on-disk field width is mandatory for compatibility.*  
   > TODO: write your answer here.
