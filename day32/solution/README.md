# Day 32 Solution Workspace

## Build and run

From this directory:

```bash
make test
make clean
```

## Answers

1. What is the difference between a lock-free queue and a mutex-based queue?  
   *Hint: compare blocking behavior, contention handling, and overhead.*  
   > TODO: write your answer here.

2. Why must the producer write the data to the array before updating the atomic head index?  
   *Hint: think about what the consumer sees after observing new head value.*  
   > TODO: write your answer here.

3. What does compiler reordering mean in the context of multithreading?  
   *Hint: optimization may change operation order unless synchronization prevents it.*  
   > TODO: write your answer here.

4. How do you check if an SPSC ring buffer is full?  
   *Hint: use next producer position and compare with tail.*  
   > TODO: write your answer here.

5. What is the default memory order used by standard C11 atomic operations?  
   *Hint: default `atomic_load/atomic_store` variants are the strongest ordering.*  
   > TODO: write your answer here.

6. Why is one slot often intentionally left unused in a ring buffer?  
   *Hint: this simplifies full-vs-empty detection.*  
   > TODO: write your answer here.

7. Why is this queue design called Single-Producer Single-Consumer?  
   *Hint: identify which thread owns each write-side index.*  
   > TODO: write your answer here.

8. What kind of bug can happen if head or tail are plain `size_t` instead of atomic?  
   *Hint: think data races and stale reads across cores.*  
   > TODO: write your answer here.
