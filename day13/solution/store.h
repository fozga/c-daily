#pragma once
#include <stdbool.h>

/* Opaque handle — consumers cannot see the internals. */
typedef struct store store_t;

/* Creates a new store with the given initial capacity.
   Returns NULL on allocation failure. */
store_t* store_create(int initial_capacity);

/* Frees all memory. Safe to call with NULL. */
void store_destroy(store_t* s);

/* Inserts or updates key->value. Returns true on success, false on alloc failure. */
bool store_put(store_t* s, const char* key, int value);

/* Looks up a key. Returns true and writes to *out_val if found. */
bool store_get(const store_t* s, const char* key, int* out_val);

/* Removes a key. Returns true if found and removed. */
bool store_remove(store_t* s, const char* key);

/* Returns current number of entries. */
int store_count(const store_t* s);
