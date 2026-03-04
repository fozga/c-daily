#pragma once
#include <stdbool.h>
#include <stddef.h>

typedef struct slist_node {
    int value;
    struct slist_node* next;
} slist_node_t;

typedef struct {
    slist_node_t* head;
    size_t count;
} slist_t;

void slist_init(slist_t* list);
void slist_destroy(slist_t* list);
bool slist_push_front(slist_t* list, int value);

/* Internal invariant check (exposed for testing purposes) */
void slist_verify_invariants(const slist_t* list);

/* Fault injection API: tells the custom allocator to fail on the Nth allocation.
   Set to -1 to disable fault injection. */
void test_set_malloc_fail_at(int n);
