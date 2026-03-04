# Day 13 Solution Workspace

## Build and run

- `make test` - build and run tests.
- `make asan` - run tests with AddressSanitizer.
- `make valgrind` - run tests under Valgrind.
- `make clean` - remove generated binaries.

## Answers

1. What is an opaque pointer and why must the struct be defined in the `.c` file?  
   *Hint: think about encapsulation and preventing consumers from depending on internals.*  
   > TODO: write your answer here.

2. What does `static` mean at file scope in C?  
   *Hint: this is about linkage visibility across translation units.*  
   > TODO: write your answer here.

3. If a consumer only has `store.h`, can they read the internals of `store_t`? Why or why not?  
   *Hint: consider what information a forward declaration does and does not provide.*  
   > TODO: write your answer here.

4. What is the ABI benefit of opaque types compared to fully public structs?  
   *Hint: changing internal layout should not force consumer recompilation contracts.*  
   > TODO: write your answer here.

5. What are the downsides of the opaque pointer pattern?  
   *Hint: think heap allocation, pointer indirection, and boilerplate.*  
   > TODO: write your answer here.

6. Why should tests for encapsulation include only the public header?  
   *Hint: this validates real consumer constraints.*  
   > TODO: write your answer here.

7. Why are NULL-safe destroy functions useful in C APIs?  
   *Hint: simplify cleanup paths and error handling code.*  
   > TODO: write your answer here.

8. What role do private headers like `store_internal.h` play in module design?  
   *Hint: separate implementation details from stable API surface.*  
   > TODO: write your answer here.
