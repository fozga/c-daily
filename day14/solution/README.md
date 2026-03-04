# Day 14 Solution Workspace

## Build and run

- `make lib` - build `libcdrills.a`.
- `make cli` - build the `cdrills` CLI.
- `make run` - run a demo CLI command.
- `make test` - build and run integration smoke tests.
- `make asan` - run smoke tests with AddressSanitizer.
- `make valgrind` - run smoke tests with Valgrind.
- `make clean` - remove binaries, objects, and archive outputs.

## Answers

1. What is the difference between a static library (`.a`) and a shared library (`.so`)?  
   *Hint: compare link time vs runtime loading and deployment tradeoffs.*  
   > TODO: write your answer here.

2. What does `ar rcs` do?  
   *Hint: each flag contributes to archive creation/update behavior.*  
   > TODO: write your answer here.

3. Why does linker order matter (`gcc main.o -lfoo` vs `gcc -lfoo main.o`)?  
   *Hint: symbol resolution is typically performed left-to-right.*  
   > TODO: write your answer here.

4. What is an umbrella header and what are its downsides?  
   *Hint: convenience can increase compile dependencies and API surface.*  
   > TODO: write your answer here.

5. What is the standard exit code convention for CLI tools?  
   *Hint: success is zero; failures are nonzero and may encode categories.*  
   > TODO: write your answer here.

6. What should integration smoke tests verify beyond unit correctness?  
   *Hint: think build/link/API wiring across modules.*  
   > TODO: write your answer here.

7. Why is a `.PHONY` declaration important in Makefiles?  
   *Hint: target names can collide with real files in the working directory.*  
   > TODO: write your answer here.

8. Why might static linking be preferred in small teaching projects?  
   *Hint: consider reproducibility and simpler runtime deployment.*  
   > TODO: write your answer here.
