#pragma once
#include <stdbool.h>
#include <stddef.h>

typedef struct {
    char* key;   /* NULL if slot is empty */
    int   value;
} hash_slot_t;

typedef struct {
    hash_slot_t* slots;
    size_t       capacity;
    size_t       count;
} hashmap_t;

/* Initializes the hashmap with an initial capacity (e.g., 16). */
bool hm_init(hashmap_t* hm, size_t initial_capacity);

/* Frees the hashmap and all duplicated string keys. */
void hm_destroy(hashmap_t* hm);

/* Inserts or updates a value. Duplicates the key string.
   Automatically resizes if load factor >= 0.75. */
bool hm_put(hashmap_t* hm, const char* key, int value);

/* Retrieves a value. Returns true if found. */
bool hm_get(const hashmap_t* hm, const char* key, int* out_value);

/* Returns current number of elements. */
size_t hm_count(const hashmap_t* hm);
