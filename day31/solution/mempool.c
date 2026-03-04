#include "mempool.h"

/* Constraint for this exercise:
 * Do not use malloc/free/calloc/realloc in this implementation.
 */

int pool_init(mempool_t* p, void* backing_buffer, size_t block_size, size_t block_count) {
    (void)p;
    (void)backing_buffer;
    (void)block_size;
    (void)block_count;
    /* TODO:
     * - validate arguments
     * - ensure block_size >= sizeof(void*)
     * - link all blocks into a singly linked free-list
     */
    return -1;
}

void* pool_alloc(mempool_t* p) {
    (void)p;
    /* TODO:
     * - return NULL if free_list is empty
     * - pop one block from free_list in O(1)
     */
    return 0;
}

void pool_free(mempool_t* p, void* ptr) {
    (void)p;
    (void)ptr;
    /* TODO:
     * - push ptr back to free_list in O(1)
     */
}
