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

/* Initializes an empty list. */
void slist_init(slist_t* list);

/* Frees all nodes and resets the list to empty. */
void slist_destroy(slist_t* list);

/* Prepends a value to the front of the list. Returns false on alloc failure. */
bool slist_push_front(slist_t* list, int value);

/* Appends a value to the end of the list. Returns false on alloc failure. */
bool slist_push_back(slist_t* list, int value);

/* Removes the first occurrence of 'value'. Returns true if found and removed. */
bool slist_remove(slist_t* list, int value);

/* Returns the value at the given zero-based index.
   Returns false if index is out of bounds. */
bool slist_get_at(const slist_t* list, size_t index, int* out_value);
