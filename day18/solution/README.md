# Day 18 Solution Workspace

## Build and run

- `make test` - build and run tests.
- `make asan` - run tests with AddressSanitizer.
- `make valgrind` - run tests with Valgrind.
- `make clean` - remove generated binaries.

## Answers

**Q1: Why must the node type be declared as `struct slist_node` with a named tag, rather than an anonymous typedef struct? What compilation error occurs if you use an anonymous struct?**  

> Your answer here...

---

**Q2: Why is `free(curr); curr = curr->next;` undefined behavior (UB), and what is the correct two-step pattern that avoids it?**  

> Your answer here...

---

**Q3: Why does removing the head node require a different code path than removing a middle node? What pointer must be updated in each case?**  

> Your answer here...

---

**Q4: What is the time complexity of appending to the tail when only a `head` pointer is stored, and how would adding a `tail` pointer change both the complexity and the implementation burden?**  

> Your answer here...

---

**Q5: What does Valgrind report — and under which leak category — if `slist_destroy` is never called before process exit? How does the answer change if the head pointer has been set to NULL without freeing the nodes?**  

> Your answer here...

---

**Q6: Why must `slist_get_at` validate the index before traversal, and what undefined behavior (UB) can result if it does not?**  

> Your answer here...

---

**Q7: Why must `count` be updated atomically with every insert and remove operation? What class of bugs appears if count drifts from the actual node count?**  

> Your answer here...

---

**Q8: List all distinct edge cases that removal logic must handle correctly. For each case, describe what pointer update distinguishes it from the general case.**  

> Your answer here...
