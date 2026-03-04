#pragma once
#include <stddef.h>
#include <stdbool.h>

typedef struct {
    const char* data;
    size_t length;
} strview;

/* Creates a view from a standard NUL-terminated C-string.
   If cstr is NULL, returns a view with data=NULL and length=0. */
strview sv_from_cstr(const char* cstr);

/* Returns true if the two views contain exactly the same characters. */
bool sv_equals(strview a, strview b);

/* Returns a new view with leading and trailing whitespace (' ', '\t', '\n', '\r') removed.
   Does not modify the original data. */
strview sv_trim(strview sv);

/* Finds the first occurrence of 'target' inside 'sv'.
   Returns the index if found, or -1 if not found. */
int sv_find(strview sv, char target);

/* Splits 'sv' by the given 'delimiter' into 'out_left' and 'out_right'.
   Returns true if the delimiter was found and the split occurred.
   Returns false if the delimiter was not found (and does not modify out params). */
bool sv_split_once(strview sv, char delimiter, strview* out_left, strview* out_right);
