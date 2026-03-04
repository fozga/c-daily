# Day 12 Solution Workspace

## Build and run

- `make test` - build and run tests.
- `make asan` - run tests with AddressSanitizer.
- `make layout_check` - rebuild with `-Wpadded` to inspect padding warnings.
- `make valgrind` - run tests under Valgrind.
- `make clean` - remove generated binaries.

## Answers

1. Why does the compiler add padding between struct fields?  
   *Hint: alignment constraints affect efficient/safe memory access.*  
   > TODO: write your answer here.

2. How does `offsetof(struct S, field)` help diagnose layout issues?  
   *Hint: it gives exact byte offsets of fields in memory.*  
   > TODO: write your answer here.

3. Why is `__attribute__((packed))` dangerous on some architectures?  
   *Hint: think unaligned accesses, performance, and potential traps.*  
   > TODO: write your answer here.

4. What is "tail padding" and when does it appear?  
   *Hint: arrays of structs require each element to preserve alignment.*  
   > TODO: write your answer here.

5. How can you enforce a struct size at compile time using `_Static_assert`?  
   *Hint: compare `sizeof(type)` against expected constant.*  
   > TODO: write your answer here.

6. Why can raw `fwrite`/`fread` of structs break binary compatibility?  
   *Hint: field order, padding, and ABI details may vary.*  
   > TODO: write your answer here.

7. Why are fixed-width types preferred in serialized formats?  
   *Hint: deterministic field sizes across platforms.*  
   > TODO: write your answer here.

8. What does `-Wpadded` help you discover during debugging?  
   *Hint: compiler-inserted layout gaps that are otherwise invisible.*  
   > TODO: write your answer here.
