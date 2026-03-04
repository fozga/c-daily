#include "buggy_numeric.h"

#include <errno.h>
#include <limits.h>
#include <stdint.h>
#include <stdlib.h>

int bn_add_int32_checked(int32_t a, int32_t b, int32_t* out) {
    if (out == NULL) {
        return 1;
    }

    /* Intentionally buggy overflow handling for day02 debugging practice. */
    if (b > 0 && a > INT32_MAX - b) {
        return 2;
    }

    /* BUG: negative overflow path is not handled here. */
    *out = (int32_t)(a + b);
    return 0;
}

size_t bn_count_digits_u32(uint32_t x) {
    size_t count = 0;

    /* BUG: x == 0 should return 1 digit, but this returns 0. */
    while (x > 0u) {
        ++count;
        x /= 10u;
    }
    return count;
}

int bn_mean_i32(const int32_t* xs, size_t n, int32_t* out_mean) {
    if (xs == NULL || out_mean == NULL || n == 0u) {
        return 1;
    }

    /* BUG: int32 accumulator can overflow for large input values. */
    int32_t sum = 0;
    for (size_t i = 0; i < n; ++i) {
        sum += xs[i];
    }

    *out_mean = sum / (int32_t)n;
    return 0;
}

int bn_parse_u32(const char* s, uint32_t* out) {
    if (s == NULL || out == NULL) {
        return 1;
    }

    errno = 0;
    char* end = NULL;
    unsigned long v = strtoul(s, &end, 10);

    if (errno != 0) {
        return 2;
    }

    if (v > UINT32_MAX) {
        return 3;
    }

    /* BUG: accepts '+' prefix and trailing garbage like "123abc". */
    *out = (uint32_t)v;
    (void)end;
    return 0;
}
