#include "slist.h"

#include <stdlib.h>

void slist_init(slist_t* list) {
    (void)list;
    /* TODO: initialize head to NULL and count to 0. */
}

void slist_destroy(slist_t* list) {
    (void)list;
    /* TODO: free all nodes and reset list fields. */
}

bool slist_push_front(slist_t* list, int value) {
    (void)list;
    (void)value;
    /* TODO: allocate a new node and insert at list head. */
    return false;
}

bool slist_push_back(slist_t* list, int value) {
    (void)list;
    (void)value;
    /* TODO: allocate a new node and append at list tail. */
    return false;
}

bool slist_remove(slist_t* list, int value) {
    (void)list;
    (void)value;
    /* TODO: remove first matching value from list. */
    return false;
}

bool slist_get_at(const slist_t* list, size_t index, int* out_value) {
    (void)list;
    (void)index;
    (void)out_value;
    /* TODO: validate bounds, traverse, and write out_value. */
    return false;
}
