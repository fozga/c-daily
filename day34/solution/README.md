# Day 34 Solution Workspace

## Build and run

From this directory:

```bash
make test
make asan
make valgrind
make clean
```

## Answers

1. Why is a ring buffer better than moving array elements down when reading?  
   *Hint: compare algorithmic complexity and memory traffic.*  
   > TODO: write your answer here.

2. How do you distinguish between "full" and "empty" in a ring buffer without a count variable?  
   *Hint: empty-slot pattern uses different conditions for head/tail.*  
   > TODO: write your answer here.

3. If an array has size 16, how many useful elements can the "one empty slot" ring buffer hold?  
   *Hint: one slot is intentionally reserved.*  
   > TODO: write your answer here.

4. What is the bitwise equivalent of `x % 32`?  
   *Hint: 32 is a power of two, so use a mask.*  
   > TODO: write your answer here.

5. What happens if the producer pushes data faster than the consumer pops it?  
   *Hint: eventually the buffer reaches full condition and pushes fail or overwrite.*  
   > TODO: write your answer here.

6. Why must head and tail wrap around with modulo logic?  
   *Hint: array size is fixed but stream is conceptually unbounded.*  
   > TODO: write your answer here.

7. What bug appears if `rb_push` writes data before checking full condition?  
   *Hint: unread bytes may be overwritten.*  
   > TODO: write your answer here.

8. Why is FIFO order important for streaming interfaces like UART?  
   *Hint: message byte ordering must remain stable end-to-end.*  
   > TODO: write your answer here.
