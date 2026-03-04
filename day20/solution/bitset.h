#pragma once
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

typedef struct {
    uint64_t* blocks;
    size_t    num_bits;
    size_t    num_blocks;
} bitset_t;

/* Initializes a bitset capable of storing 'num_bits'. All bits set to 0. */
bool bs_init(bitset_t* bs, size_t num_bits);

/* Frees the bitset. */
void bs_destroy(bitset_t* bs);

/* Sets the bit at 'index' to 1. Returns false if out of bounds. */
bool bs_set(bitset_t* bs, size_t index);

/* Clears the bit at 'index' to 0. Returns false if out of bounds. */
bool bs_clear(bitset_t* bs, size_t index);

/* Toggles the bit at 'index'. Returns false if out of bounds. */
bool bs_toggle(bitset_t* bs, size_t index);

/* Returns true if the bit at 'index' is 1, false if 0 or out of bounds. */
bool bs_test(const bitset_t* bs, size_t index);
