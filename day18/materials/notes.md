# Day 18 Notes - Singly linked lists in C

## 1) Linked list structure in C

A singly linked list node stores payload plus pointer to next node.
Self-referential structs require a named struct tag so the type can appear
inside its own definition:

### Example

```c
/* The struct tag 'slist_node' must be named so the next pointer can
   reference the same type before the typedef is complete. */
typedef struct slist_node {
    int               value;
    struct slist_node *next;  /* NULL in the last node */
} slist_node_t;

typedef struct {
    slist_node_t *head;   /* NULL when list is empty */
    size_t        count;
} slist_t;
```

Using an anonymous `typedef struct { ... } slist_node_t` would make
`struct slist_node` an incomplete type at the point of the `next` field
declaration — a compilation error.

## 2) Head management strategies

Two common approaches:

1. Dummy/sentinel head node
2. Direct head pointer

This exercise uses a container struct (`slist_t`) that holds:
- `slist_node_t* head` — entry point, `NULL` when list is empty
- `size_t count` — always kept consistent with the actual node count

Using a container struct keeps metadata and pointers together and avoids
passing a pointer-to-pointer everywhere.

## 3) Traversal pattern

### Example

```c
/* Safe read-only traversal. */
for (slist_node_t *curr = list->head; curr != NULL; curr = curr->next) {
    printf("%d\n", curr->value);
}
```

Always test `curr != NULL` before dereferencing `curr->value` or `curr->next`.
An empty list has `head == NULL`; the loop body never executes.

## 4) Safe deletion during traversal

Reading `curr->next` after calling `free(curr)` is undefined behavior (UB) —
the memory was returned to the allocator and its contents are unpredictable.

### Example

```c
/* UNSAFE — use-after-free */
slist_node_t *curr = list->head;
while (curr != NULL) {
    free(curr);
    curr = curr->next;   /* UB: curr was just freed */
}

/* SAFE — save next before freeing */
slist_node_t *curr = list->head;
while (curr != NULL) {
    slist_node_t *next = curr->next;   /* save before free */
    free(curr);
    curr = next;
}
```

## 5) Removing a specific node

Removing requires tracking two pointers simultaneously:
- `curr` — the candidate node to examine
- `prev` — the node immediately before `curr` (or `NULL` for the head)

### Example

```c
slist_node_t *prev = NULL;
slist_node_t *curr = list->head;

while (curr != NULL) {
    if (curr->value == target) {
        if (prev == NULL) {
            list->head = curr->next;   /* removing the head node */
        } else {
            prev->next = curr->next;   /* bypass curr */
        }
        free(curr);
        list->count--;
        return 1;   /* found and removed */
    }
    prev = curr;
    curr = curr->next;
}
return 0;   /* not found */
```

Edge cases that must be tested:
- empty list (`list->head == NULL`)
- single-node list (head and tail are the same node)
- value not present in the list
- removing the head vs. a middle vs. the tail node

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
