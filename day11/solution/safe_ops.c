#include "safe_ops.h"

#include "macros.h"

int so_min(int a, int b) {
    (void)a;
    (void)b;
    /* TODO: implement using corrected MAX macro logic once macro hazards are fixed. */
    return 0;
}

int so_clamp(int val, int lo, int hi) {
    (void)val;
    (void)lo;
    (void)hi;
    /* TODO: implement using a safe CLAMP macro after it is added/fixed. */
    return 0;
}

void so_swap(int* a, int* b) {
    (void)a;
    (void)b;
    /* TODO: validate pointers and swap values using corrected SWAP_INT macro. */
}
