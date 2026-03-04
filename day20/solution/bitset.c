#include "bitset.h"

#include <stdlib.h>

bool bs_init(bitset_t* bs, size_t num_bits) {
    (void)bs;
    (void)num_bits;
    /* TODO: allocate blocks and zero-initialize bitset state. */
    return false;
}

void bs_destroy(bitset_t* bs) {
    (void)bs;
    /* TODO: free storage and reset structure fields. */
}

bool bs_set(bitset_t* bs, size_t index) {
    (void)bs;
    (void)index;
    /* TODO: set indexed bit using uint64_t mask. */
    return false;
}

bool bs_clear(bitset_t* bs, size_t index) {
    (void)bs;
    (void)index;
    /* TODO: clear indexed bit using uint64_t mask. */
    return false;
}

bool bs_toggle(bitset_t* bs, size_t index) {
    (void)bs;
    (void)index;
    /* TODO: toggle indexed bit using uint64_t mask. */
    return false;
}

bool bs_test(const bitset_t* bs, size_t index) {
    (void)bs;
    (void)index;
    /* TODO: bounds-check and return whether indexed bit is set. */
    return false;
}
