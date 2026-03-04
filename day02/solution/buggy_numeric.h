#ifndef BUGGY_NUMERIC_H
#define BUGGY_NUMERIC_H

#include <stddef.h>
#include <stdint.h>

/*
 * Adds two int32 values.
 * Returns 0 on success.
 * Returns nonzero on overflow or invalid arguments.
 */
int bn_add_int32_checked(int32_t a, int32_t b, int32_t* out);

/* Returns the number of base-10 digits in x. */
size_t bn_count_digits_u32(uint32_t x);

/*
 * Computes integer mean of xs[0..n-1].
 * Returns 0 on success, nonzero on invalid args (including n == 0).
 * Must be safe for large values.
 */
int bn_mean_i32(const int32_t* xs, size_t n, int32_t* out_mean);

/*
 * Parses an unsigned 32-bit decimal integer from s.
 * Returns 0 on success, nonzero on validation/range errors.
 * Leading '+' or '-' should be rejected. Empty input should be rejected.
 */
int bn_parse_u32(const char* s, uint32_t* out);

#endif
