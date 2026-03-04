# Day 18 Solution Workspace

## Build and run

- `make test` - build and run tests.
- `make asan` - run tests with AddressSanitizer.
- `make valgrind` - run tests with Valgrind.
- `make clean` - remove generated binaries.

## Answers

1. Why must you declare the node struct as `struct node` rather than just an anonymous typedef?  
   *Hint: self-referential pointers need a named struct tag.*  
   > TODO: write your answer here.

2. What is the danger of iterating a list with `free(curr); curr = curr->next;`?  
   *Hint: consider object lifetime and pointer validity after free.*  
   > TODO: write your answer here.

3. Why is deleting the head node a special case compared to deleting a middle node?  
   *Hint: the list's external entry pointer must be updated.*  
   > TODO: write your answer here.

4. What is the time complexity of appending to the tail of a singly linked list if you only store a head pointer?  
   *Hint: think about traversal cost to find the last node.*  
   > TODO: write your answer here.

5. What memory issues does Valgrind report if you forget to implement `slist_destroy`?  
   *Hint: all allocated nodes remain reachable/lost at process exit.*  
   > TODO: write your answer here.

6. Why should `slist_get_at` validate bounds before traversal?  
   *Hint: prevent NULL dereference and undefined behavior.*  
   > TODO: write your answer here.

7. Why must count metadata be updated consistently on insert/remove?  
   *Hint: stale count breaks API invariants and tests.*  
   > TODO: write your answer here.

8. What edge cases should always be unit-tested in list removal logic?  
   *Hint: empty, head, tail, middle, and missing value cases.*  
   > TODO: write your answer here.
