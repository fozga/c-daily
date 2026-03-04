# Day 08 Solution Workspace

## Build and run

- `make test` - build and run tests.
- `make asan` - run tests with AddressSanitizer.
- `make valgrind` - run tests under Valgrind.
- `make clean` - remove generated binaries.

## Answers

1. Why are `qsort` comparator params `const void*` instead of typed pointers?  
   *Hint: think about generic algorithms operating on arbitrary element types.*  
   > TODO: write your answer here.

2. Why is `return a - b` as a comparator dangerous for signed integers?  
   *Hint: consider overflow rules for signed arithmetic in C.*  
   > TODO: write your answer here.

3. What happens if you call `bsearch` on an unsorted array?  
   *Hint: binary search depends on a monotonic ordering invariant.*  
   > TODO: write your answer here.

4. How do you sort an array of structs by a string field?  
   *Hint: compare `char[]` fields with `strcmp` in a comparator callback.*  
   > TODO: write your answer here.

5. Why is `qsort` not guaranteed to be stable?  
   *Hint: the C standard specifies ordering correctness, not equal-element order preservation.*  
   > TODO: write your answer here.

6. What comparator properties must hold for `qsort` and `bsearch` to behave correctly?  
   *Hint: think transitivity, consistent equality handling, and total ordering expectations.*  
   > TODO: write your answer here.

7. How should you safely compare two `int32_t` values in a comparator without overflow risk?  
   *Hint: use relational checks to return -1/0/1 rather than arithmetic subtraction.*  
   > TODO: write your answer here.

8. Why must the same logical ordering be used for both `qsort` and `bsearch`?  
   *Hint: search correctness relies on exactly the ordering used to sort the array.*  
   > TODO: write your answer here.
