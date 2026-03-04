# Day 18 Notes - Singly linked lists in C

## 1) Linked list structure in C

A singly linked list node stores payload plus pointer to next node:

- `value` data field
- `next` link to following node or `NULL`

Self-referential type pattern:
- define `struct slist_node` and use `struct slist_node* next`

This pattern is fundamental for dynamic, pointer-based data structures.

## 2) Head management strategies

Two common approaches:

1. Dummy/sentinel head node
2. Direct head pointer

This exercise uses a container:
- `slist_t` with `slist_node_t* head`
- plus `count` tracking current size

Using a container struct helps keep metadata and pointers together.

## 3) Traversal pattern

Canonical traversal:

`for (node_t* curr = head; curr != NULL; curr = curr->next) { ... }`

Always test `curr != NULL` before dereferencing fields like `curr->value` or
`curr->next`.

## 4) Safe deletion during traversal

Unsafe pattern:
- `free(curr); curr = curr->next;`  (use-after-free)

Safe pattern:
1. Save next pointer first: `next = curr->next`
2. Free current node
3. Advance: `curr = next`

Never read from a node after `free`.

## 5) Removing a specific node

Removing requires tracking both:
- `curr` (candidate node)
- `prev` (node before candidate)

Cases:
- remove head (`prev == NULL`) -> update `list->head`
- remove middle/tail -> set `prev->next = curr->next`

Edge cases matter:
- empty list
- single-node list
- value not found

## Common mistakes

- Forgetting to initialize `head` and `count`.
- Dereferencing `NULL` when list is empty.
- Use-after-free during delete loops.
- Not updating `count` consistently.
- Leaking nodes by skipping `slist_destroy`.

## C vs C++

- C requires manual memory management for each node.
- C++ often uses `std::forward_list` or smart pointers.
- In C, ownership contracts must be explicit in API documentation.
