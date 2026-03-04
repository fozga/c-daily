#include "store.h"
#include "store_internal.h"

store_t* store_create(int initial_capacity) {
    (void)initial_capacity;
    /* TODO: allocate store and slot array for linear-probing hash table. */
    return NULL;
}

void store_destroy(store_t* s) {
    (void)s;
    /* TODO: free all owned allocations safely (NULL-safe). */
}

bool store_put(store_t* s, const char* key, int value) {
    (void)s;
    (void)key;
    (void)value;
    /* TODO: hash key, insert/update with linear probing, resize if needed. */
    return false;
}

bool store_get(const store_t* s, const char* key, int* out_val) {
    (void)s;
    (void)key;
    (void)out_val;
    /* TODO: probe for key and return stored value if found. */
    return false;
}

bool store_remove(store_t* s, const char* key) {
    (void)s;
    (void)key;
    /* TODO: remove key while preserving probing invariants. */
    return false;
}

int store_count(const store_t* s) {
    (void)s;
    /* TODO: return current entry count from store state. */
    return -1;
}
