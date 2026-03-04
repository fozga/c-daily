# Day 28 Solution Workspace

## Build and run

- `make test` - build and run matcher2 tests.
- `make asan` - run tests with AddressSanitizer.
- `make valgrind` - run tests under Valgrind.
- `make clean` - remove generated binaries.

## Answers

1. How does recursive-descent parsing work at a high level?  
   *Hint: parse functions consume grammar constructs left-to-right.*  
   > TODO: write your answer here.

2. What is the ASCII range for lowercase letters (`a-z`)?  
   *Hint: decimal codes from `a` to `z`.*  
   > TODO: write your answer here.

3. What makes `[^abc]` different from `[abc]` in matching logic?  
   *Hint: inclusion vs exclusion predicate.*  
   > TODO: write your answer here.

4. How should your parser behave if a `[` is opened but `]` is never found?  
   *Hint: fail safely with no crash/infinite loop.*  
   > TODO: write your answer here.

5. Why does backward compatibility matter even in a personal project?  
   *Hint: existing tests/users rely on old behavior contracts.*  
   > TODO: write your answer here.

6. Why must `-i` case-folding apply to bracket ranges too?  
   *Hint: class semantics should remain consistent with global matcher mode.*  
   > TODO: write your answer here.

7. What is the parser difference between escaped `\\n` and literal `n` in pattern text?  
   *Hint: escape decoding transforms token meaning at runtime.*  
   > TODO: write your answer here.

8. Why should malformed patterns return "no match" instead of causing undefined behavior?  
   *Hint: input robustness and tool reliability under bad patterns.*  
   > TODO: write your answer here.
