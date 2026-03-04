#include "slist_defensive.h"

#include <stdlib.h>

static int g_malloc_fail_at = -1;
static int g_alloc_counter = 0;

static void* test_malloc(size_t size) {
    if (g_malloc_fail_at >= 0 && g_alloc_counter == g_malloc_fail_at) {
        ++g_alloc_counter;
        return NULL;
    }
    ++g_alloc_counter;
    return malloc(size);
}

#define MALLOC_SEAM(size) test_malloc(size)

void test_set_malloc_fail_at(int n) {
    g_malloc_fail_at = n;
    g_alloc_counter = 0;
}

void slist_init(slist_t* list) {
    if (list == NULL) {
        return;
    }
    list->head = NULL;
    list->count = 0;
}

void slist_verify_invariants(const slist_t* list) {
    (void)list;
    /* TODO: learner implements traversal + assert that node count matches list->count. */
}

bool slist_push_front(slist_t* list, int value) {
    slist_node_t* n = NULL;
    if (list == NULL) {
        return false;
    }

    n = (slist_node_t*)MALLOC_SEAM(sizeof(*n));
    if (n == NULL) {
        return false;
    }

    n->value = value;
    n->next = list->head;
    list->head = n;
    list->count += 1u;

    /* TODO: call slist_verify_invariants(list) after mutation. */
    return true;
}

void slist_destroy(slist_t* list) {
    slist_node_t* curr = NULL;
    slist_node_t* next = NULL;

    if (list == NULL) {
        return;
    }

    curr = list->head;
    while (curr != NULL) {
        next = curr->next;
        free(curr);
        curr = next;
    }

    list->head = NULL;
    list->count = 0;
    /* TODO: call slist_verify_invariants(list) after mutation. */
}
