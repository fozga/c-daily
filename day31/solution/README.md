# Day 31 Solution Workspace

## Build and run

- `make test` - build and run pool tests.
- `make asan` - run tests with AddressSanitizer.
- `make valgrind` - run tests under Valgrind.
- `make clean` - remove generated binaries.

## Answers

1. What is heap fragmentation?  
   *Hint: free memory exists but is split into unusable pieces for requested sizes.*  
   > TODO: write your answer here.

2. Why does `malloc` have non-deterministic execution time?  
   *Hint: allocator metadata scans/coalescing vary with heap state.*  
   > TODO: write your answer here.

3. How does a free-list store tracking pointers without using extra memory?  
   *Hint: freed block payload stores next free pointer.*  
   > TODO: write your answer here.

4. What happens to the free-list if you call `pool_free` on the same pointer twice?  
   *Hint: linked structure can become corrupted or cyclic.*  
   > TODO: write your answer here.

5. Why must the block size be at least `sizeof(void*)`?  
   *Hint: free-list pointer must fit inside each free block.*  
   > TODO: write your answer here.

6. Why is static pre-allocation attractive for real-time systems?  
   *Hint: deterministic memory behavior and reduced runtime surprises.*  
   > TODO: write your answer here.

7. Why should pool APIs define ownership and lifetime rules clearly?  
   *Hint: avoids invalid frees and aliasing misuse.*  
   > TODO: write your answer here.

8. What invariant defines an empty pool?  
   *Hint: free-list head pointer state indicates no available blocks.*  
   > TODO: write your answer here.
