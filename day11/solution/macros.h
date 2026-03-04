#ifndef MACROS_H
#define MACROS_H

#include <stddef.h>

/* BUG: double-evaluation hazard — fix me */
#define MAX(a, b) (a > b ? a : b)

/* BUG: missing body parentheses — fix me */
#define SQUARE(x) x * x

/* BUG: missing do-while wrapper — fix me */
#define SWAP_INT(a, b) { int _t = a; a = b; b = _t; }

/* Safe version (already correct — use as reference): */
#define ARRAY_LEN(arr) (sizeof(arr) / sizeof((arr)))

/* TODO: Add CLAMP(val, lo, hi) macro — safe, no double evaluation */

#endif /* MACROS_H */
