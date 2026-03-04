#include "broken_pointers.h"

#include <stdlib.h>

int list_append(node_t** head_ref, int value) {
    node_t* n = NULL;
    node_t* tail = NULL;

    if (head_ref == NULL) {
        return -1;
    }

    n = (node_t*)malloc(sizeof(*n));
    if (n == NULL) {
        return -1;
    }
    n->value = value;
    n->next = NULL;

    if (*head_ref == NULL) {
        *head_ref = n;
        return 0;
    }

    tail = *head_ref;
    while (tail->next != NULL) {
        tail = tail->next;
    }
    tail->next = n;
    return 0;
}

void list_reverse(node_t** head_ref) {
    node_t* prev = NULL;
    node_t* curr = NULL;
    node_t* next = NULL;

    if (head_ref == NULL || *head_ref == NULL) {
        return;
    }

    curr = *head_ref;
    while (curr != NULL) {
        next = curr->next;
        curr->next = prev;
        prev = curr;
        curr = next;
    }

    /* INTENTIONAL BUG:
       curr is NULL after the loop, so curr->next dereferences NULL and crashes.
       This is meant for GDB debugging practice. */
    prev->next = curr->next;
    *head_ref = prev;
}

void list_free(node_t* head) {
    node_t* next = NULL;
    while (head != NULL) {
        next = head->next;
        free(head);
        head = next;
    }
}
