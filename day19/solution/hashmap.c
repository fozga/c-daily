#include "hashmap.h"

#include <stdint.h>
#include <stdlib.h>

static bool hm_resize(hashmap_t* hm, size_t new_cap);

static uint32_t hash_fnv1a(const char* key) {
    const unsigned char* p = (const unsigned char*)key;
    uint32_t h = 2166136261u;
    while (*p != '\0') {
        h ^= (uint32_t)(*p);
        h *= 16777619u;
        ++p;
    }
    return h;
}

bool hm_init(hashmap_t* hm, size_t initial_capacity) {
    (void)hm;
    (void)initial_capacity;
    (void)hash_fnv1a;
    (void)hm_resize;
    /* TODO: allocate slot array and initialize hashmap state. */
    return false;
}

void hm_destroy(hashmap_t* hm) {
    (void)hm;
    /* TODO: free duplicated keys and slot array, then zero struct fields. */
}

bool hm_put(hashmap_t* hm, const char* key, int value) {
    (void)hm;
    (void)key;
    (void)value;
    /* TODO: implement insert/update with linear probing and resizing. */
    return false;
}

bool hm_get(const hashmap_t* hm, const char* key, int* out_value) {
    (void)hm;
    (void)key;
    (void)out_value;
    /* TODO: implement lookup with same probing strategy as hm_put. */
    return false;
}

size_t hm_count(const hashmap_t* hm) {
    (void)hm;
    /* TODO: return live element count. */
    return 0;
}

static bool hm_resize(hashmap_t* hm, size_t new_cap) {
    (void)hm;
    (void)new_cap;
    /* TODO: allocate new slots and rehash all existing entries. */
    return false;
}
