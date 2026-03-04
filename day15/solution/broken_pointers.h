#pragma once

typedef struct node {
    int value;
    struct node* next;
} node_t;

/* Appends a new node to the end of the list.
   *head_ref may be NULL if the list is empty.
   Returns 0 on success, -1 on allocation failure. */
int list_append(node_t** head_ref, int value);

/* Reverses the linked list in-place.
   Updates *head_ref to point to the new head. */
void list_reverse(node_t** head_ref);

/* Frees all nodes in the list. */
void list_free(node_t* head);
