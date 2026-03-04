#pragma once
#include <stddef.h>
#include <stdint.h>

typedef struct mempool {
    uint8_t* buffer;
    size_t   block_size;
    size_t   block_count;
    void*    free_list;
} mempool_t;

/* Initializes pool over provided static buffer. Returns 0 on success, -1 on invalid args. */
int pool_init(mempool_t* p, void* backing_buffer, size_t block_size, size_t block_count);

/* Returns pointer to one block, or NULL if pool exhausted. */
void* pool_alloc(mempool_t* p);

/* Returns block to pool. Undefined behavior if ptr is not from this pool. */
void pool_free(mempool_t* p, void* ptr);
