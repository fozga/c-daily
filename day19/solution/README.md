# Day 19 Solution Workspace

## Build and run

- `make test` - build and run tests.
- `make asan` - run tests with AddressSanitizer.
- `make valgrind` - run tests under Valgrind.
- `make clean` - remove generated binaries.

## Answers

1. Why is open addressing often faster than chaining on modern CPUs?  
   *Hint: compare pointer chasing vs contiguous array scans.*  
   > TODO: write your answer here.

2. Why must the hash map duplicate the string key (`strdup`) instead of just storing the `const char*`?  
   *Hint: ownership and caller lifetime are not guaranteed.*  
   > TODO: write your answer here.

3. What happens if you resize an open-addressed map by just copying the array using `memcpy`?  
   *Hint: probe positions depend on `hash % capacity`.*  
   > TODO: write your answer here.

4. What is a tombstone and why is it necessary for deletion in linear probing?  
   *Hint: empty slot termination can break probe chains after deletions.*  
   > TODO: write your answer here.

5. What does the load factor represent?  
   *Hint: ratio of stored elements to available capacity.*  
   > TODO: write your answer here.

6. Why can overwriting an existing key leak memory if done incorrectly?  
   *Hint: old duplicated key/value resources may become unreachable.*  
   > TODO: write your answer here.

7. Why should resize reinsert entries instead of preserving old indices?  
   *Hint: modulo arithmetic changes under new capacity.*  
   > TODO: write your answer here.

8. How do collisions affect complexity as load factor approaches 1.0?  
   *Hint: probe sequences get longer and average operation cost rises.*  
   > TODO: write your answer here.
